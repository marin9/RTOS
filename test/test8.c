#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	semaphore

static void task0(void *args){
	int i;
	while(1){
		os_sem_take(1);
		for(i=0;i<5;++i){
			uart_print((char*)args);
			os_task_sleep(1000);
		}
		os_sem_give(1);
		os_task_sleep(1000);
	}
}


void test8(){
	os_sem_init(1, 1);
	os_task_create(task0, "T 0\r\n", 2, 2024, 0);
	os_task_create(task0, "T  1\r\n", 2, 2024, 0);
	os_task_create(task0, "T   2\r\n", 2, 2024, 0);
	os_task_create(task0, "T    3\r\n", 2, 2024, 0);
	os_task_create(task0, "T     4\r\n", 2, 2024, 0);
}
