#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	timers

static void task1(){
	while(1){
		uart_print(".\r\n");
		os_task_sleep(1000);
	}
}

static void t1(){
	uart_print(" T1\r\n");
}

static void t2(){
	uart_print("  T2\r\n");
}

static void t3(){
	uart_print("   T3\r\n");
}


void test14(){
	os_tmr_init(0, 0, 1000, t1);
	os_tmr_init(1, 10000, 1000, t2);
	os_tmr_init(2, 15000, 0, t3);

	os_tmr_start(0);
	os_tmr_start(1);
	os_tmr_start(2);

	os_task_create(task1, 0, 1, 1024, 0);
}
