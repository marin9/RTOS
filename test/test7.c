#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_wakeup


static void task0(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(2000);
	}
}

static void taskX(){
	int i;
	char buffer[16];

	while(1){
		while(!uart_read(0, buffer, 1)){
			os_task_sleep(100);
		}
		for(i=0;i<10;++i){
			os_task_wakeup(i);
		}
	}
}


void test7(){
	os_task_create(task0, "T 0\r\n", 1, 1024, 0);
	os_task_create(task0, "T  1\r\n", 1, 1024, 0);
	os_task_create(task0, "T   2\r\n", 1, 1024, 0);
	os_task_create(task0, "T    3\r\n", 1, 1024, 0);
	os_task_create(taskX, 0, 1, 1024, 0);
}
