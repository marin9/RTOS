#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_set_prio


static void task0(void *args){
	int i;
	for(i=0;i<5;++i){
		uart_print((char*)args);
		time_delay(1000000);
	}
	os_task_set_prio(3);
	for(i=0;i<5;++i){
		uart_print((char*)args);
		time_delay(1000000);
	}
}

static void task1(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(1000);
	}
}


void test5(){
	os_task_create(task0, "T 0\r\n", 1, 1024, 0);
	os_task_create(task1, "T  1\r\n", 2, 1024, 0);
}
