#include "api.h"
#include "time.h"
#include "device.h"

//	TEST: 
//	task_sleep

static void task1(void *args){
	char *name=(char*)args;

	while(1){
		uart_print(name);
		uart_print("\r\n");
		os_task_sleep(1000);
	}
}

static void task2(void *args){
	char *name=(char*)args;

	while(1){
		uart_print(name);
		uart_print("\r\n");
		os_task_sleep(2000);
	}
}

static void task3(void *args){
	char *name=(char*)args;

	while(1){
		uart_print(name);
		uart_print("\r\n");
		os_task_sleep(3000);
	}
}


void test5(){
	time_delay(5000000);
	os_task_create(task1, "T 0", 1, 1024, 0);
	os_task_create(task2, "T  1", 2, 1024, 0);
	os_task_create(task3, "T   2", 3, 1024, 0);
}
