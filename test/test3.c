#include "api.h"
#include "time.h"
#include "device.h"

//	TEST: 
//	task_suspend
//	task_resume

static void task(void *args){
	char *name=(char*)args;

	while(1){
		uart_print(name);
		uart_print("\r\n");
		time_delay(1000000);
	}
}

static void control(){
	time_delay(10*1000000);
	os_task_suspend(2);
	os_task_suspend(3);
	time_delay(10*1000000);
	os_task_resume(2);
	os_task_resume(3);
}


void test3(){
	time_delay(3000000);
	os_task_create(task, "T 0", 1, 1024, 0);
	os_task_create(task, "T  1", 1, 1024, 0);
	os_task_create(task, "T   2", 1, 1024, 0);
	os_task_create(task, "T    3", 1, 1024, 0);
	os_task_create(task, "T     4", 1, 1024, 0);
	os_task_create(control, 0, 1, 1024, 0);
}
