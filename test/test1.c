#include "api.h"
#include "time.h"
#include "device.h"


void task(void *args){
	char *name=(char*)args;
	while(1){
		uart_print(name);
		uart_print("\r\n");
		time_delay(1000000);
	}
}


void test1(){
	os_task_create(task, "T 0", 0, 1024, 0);
	os_task_create(task, "T  1", 0, 1024, 0);
	os_task_create(task, "T   2", 0, 1024, 0);
	os_task_create(task, "T    3", 0, 1024, 0);
	os_task_create(task, "T     4", 0, 1024, 0);
}
