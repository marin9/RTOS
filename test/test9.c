#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	mutex

static void task0(void *args){
	int i;
	while(1){
		os_mux_lock(2);
		for(i=0;i<5;++i){
			uart_print((char*)args);
			os_task_sleep(1000);
		}
		os_mux_unlock(2);
		os_task_sleep(1000);
	}
}


void test9(){
	time_delay(5000000);
	uart_print("Start\r\n");

	os_mux_init(2);
	os_task_create(task0, "T 0\r\n", 2, 2024, 0);
	os_task_create(task0, "T  1\r\n", 2, 2024, 0);
	os_task_create(task0, "T   2\r\n", 2, 2024, 0);
	os_task_create(task0, "T    3\r\n", 2, 2024, 0);
	os_task_create(task0, "T     4\r\n", 2, 2024, 0);
}
