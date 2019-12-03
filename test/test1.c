#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_create
//  task_yield

static void task(void *args){
	char *name=(char*)args;
	while(1){
		uart_print(name);
		time_delay(1000000);
	}
}


void test1(){
	os_task_create(task, "T 0\r\n", 1, 1024, 0);
	os_task_create(task, "T  1\r\n", 1, 1024, 0);
	os_task_create(task, "T   2\r\n", 1, 1024, 0);
	os_task_create(task, "T    3\r\n", 1, 1024, 0);
	os_task_create(task, "T     4\r\n", 1, 1024, 0);
}
