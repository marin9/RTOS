#include "api.h"
#include "prog.h"
#include "test.h"
#include "param.h"
#include "device.h"
#include "string.h"

#define BUFFLEN		64
#define PROG_COUNT	((int)(sizeof(programs_f)/sizeof(programs_f[0])))


static char buffer[BUFFLEN];
static char progname[BUFFLEN];
static char arguments[BUFFLEN];
static char *programs[]={
	"test1",
	"test2",
	"test3",
	"test4",
	"test5",
	"test6",
	"test7",
	"test8",
	"test9",
	"test10",
	"test11",
	"test12",
	"test13",
	"test14",
	"blink"
};
static void (*programs_f[])()={
	test1,
	test2,
	test3,
	test4,
	test5,
	test6,
	test7,
	test8,
	test9,
	test10,
	test11,
	test12,
	test13,
	test14,
	blink,
};


static int getline(char *buf, uint size){
	uint i;
	char c;

	if(!buf)
		return -1;

	i=0;
	while(i<size){
		uart_getc(&c);
		if(c==127){
			if(i>0){
				--i;
				uart_print("\b \b");
			}
			continue;
		}

		buf[i]=c;
		uart_putc(c);
		if(c=='\r'){
			break;
		}
		++i;
	}

	buf[i]=0;
	uart_print("\r\n");
	return i;
}

static void run_program(char *name, void *func, void *arg, int background){
	if(background){
		os_task_create(func, arg, 1, STACK_DEFAULT, name);
	}else{
		void (*prog_function)();
		prog_function=func;
		prog_function(arg);
	}
}

static void parse_command(char *buff, char *prog, char *args, int *bgr){
	if(*buff=='+'){
		*bgr=1;
		++buff;
	}else{
		*bgr=0;
	}

	while(*buff!=' ' && *buff!=0){
		*prog=*buff;
		++prog;
		++buff;
	}
	*prog=0;
	if(*buff==0){
		*args=0;
		return;
	}

	while(*buff==' ') ++buff;
	while(*buff!=0){
		*args=*buff;
		++args;
		++buff;
	}
	*args=0;
	return;
}


void shell(){
	int i, bgr;
	uart_print("\r\nRTOS-X\r\nMarin Bralic\r\n\r\n");

	while(1){
		uart_putc('>');
		memset(buffer, 0, BUFFLEN);
		getline(buffer, BUFFLEN);
		parse_command(buffer, progname, arguments, &bgr);

		for(i=0;i<PROG_COUNT;++i){
			if(buffer[0]==0) break;
			if(strcmp(progname, programs[i])==0){
				run_program(programs[i], programs_f[i], arguments, bgr);
				break;
			}
		}
		if(i==PROG_COUNT){
			uart_print(" Command not found.\r\n");
		}
	}
}
