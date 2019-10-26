#include "api.h"
#include "time.h"
#include "device.h"


static void task(void *args){
	int i=0;
	char *name=(char*)args;

	while(1){
		uart_print(name);
		uart_print("\r\n");
		time_delay(1000000);

		if(i==10 && os_task_getid()==6){
			os_task_term(5);
			os_task_term(4);
			os_task_exit();
		}
		++i;
	}
}


void test2(){
	os_task_create(task, "T 0", 1, 1024, 0);
	os_task_create(task, "T  1", 1, 1024, 0);
	os_task_create(task, "T   2", 1, 1024, 0);
	os_task_create(task, "T    3", 2, 1024, 0);
	os_task_create(task, "T     4", 2, 1024, 0);
}
