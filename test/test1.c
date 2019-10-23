#include "task.h"
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
	time_delay(5000000);


	interrupts_disable();
	task_create(task, "T 0", 0, 1024, 0);
	task_create(task, "T  1", 0, 1024, 0);
	task_create(task, "T   2", 0, 1024, 0);
	task_create(task, "T    3", 0, 1024, 0);
	task_create(task, "T     4", 0, 1024, 0);
	interrupts_enable();

}
