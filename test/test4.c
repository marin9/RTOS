#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	task_suspend
//	task_resume


static void task0(void *args){
	while(1){
		uart_print((char*)args);
		time_delay(1000000);
	}
}


static void taskX(){
	uart_print("task X started\r\n");
	os_task_sleep(7000);
	uart_print("suspend 2 3\r\n");
	os_task_suspend(2);
	os_task_suspend(3);
	os_task_sleep(5000);
	uart_print("resume 2 3\r\n");
	os_task_resume(2);
	os_task_resume(3);
	uart_print("task X finish\r\n");
}


void test4(){
	time_delay(5000000);
	uart_print("Start\r\n");

	os_task_create(task0, "T 0\r\n", 1, 1024, 0);
	os_task_create(task0, "T  1\r\n", 1, 1024, 0);
	os_task_create(task0, "T   2\r\n", 1, 1024, 0);
	os_task_create(taskX, 0, 3, 1024, 0);
}
