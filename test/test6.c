#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_kill


static void task0(void *args){
	while(1){
		uart_print((char*)args);
		os_task_sleep(1000);
	}
}

static void taskX(){
	os_task_sleep(5500);
	os_task_kill(2);
	os_task_kill(4);
	os_task_sleep(1500);
	uart_print("x end\r\n");
}


void test6(){
	os_task_create(task0, "T 0\r\n", 1, 1024, 0);
	os_task_create(task0, "T  1\r\n", 2, 1024, 0);
	os_task_create(task0, "T   2\r\n", 2, 1024, 0);
	os_task_create(task0, "T    3\r\n", 2, 1024, 0);
	os_task_create(taskX, "T 5\r\n", 2, 1024, 0);
}
