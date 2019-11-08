#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_join
//	task_exit

static void task0(void *args){
	int i;
	for(i=0;i<5;++i){
		uart_print((char*)args);
		os_task_sleep(1000);
	}
	os_task_exit(65);
}

static void task1(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(1000);
		os_task_join(2, 0);
	}
}

static void task2(void *args){
	int ret;
	char c[4]={0, '\r', '\n', 0};

	while(1){
		uart_print((char*)args);
		os_task_sleep(1000);
		os_task_join(2, &ret);
		c[0]=ret;
		uart_print(c);
	}
}


void test3(){
	time_delay(5000000);
	uart_print("Start\r\n");

	os_task_create(task0, "T 0\r\n", 1, 1024, 0);
	os_task_create(task1, "T  1\r\n", 1, 1024, 0);
	os_task_create(task2, "T   2\r\n", 1, 1024, 0);
}
