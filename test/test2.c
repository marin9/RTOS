#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_sleep

static void task0(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(1000);
	}
}

static void task1(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(2000);
	}
}

static void task2(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(3000);
	}
}

static void taskX(void *args){
	int i;
	while(1){
		os_task_sleep(10*1000);

		for(i=0;i<5;++i){
			uart_print((char*)args);
			time_delay(1000000);
		}
	}
}

void test2(){
	os_task_create(task0, "T 0\r\n", 1, 1024, 0);
	os_task_create(task1, "T  1\r\n", 1, 1024, 0);
	os_task_create(task2, "T   2\r\n", 1, 1024, 0);
	os_task_create(taskX, "T    3\r\n", 2, 1024, 0);
}
