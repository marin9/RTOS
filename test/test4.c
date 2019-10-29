#include "api.h"
#include "time.h"
#include "device.h"

//	TEST: 
//	task_set_prio

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
	os_task_set_prio(3, 2);
}


void test4(){
	time_delay(3000000);
	os_task_create(task, "T 0", 1, 1024, 0);
	os_task_create(task, "T  1", 1, 1024, 0);
	os_task_create(task, "T   2", 1, 1024, 0);
	os_task_create(control, 0, 1, 1024, 0);
}
