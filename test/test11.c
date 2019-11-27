#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	event_set
//	event_wait


static void task0(){
	while(1){
		os_event_wait_all(0, 0x01);
		uart_print("T0: 0x01\r\n");
	}
}

static void task1(){
	while(1){
		os_event_wait_all(0, 0x02);
		uart_print("T1: 0x02\r\n");
	}
}

static void task2(){
	while(1){
		os_event_wait_all(0, 0x03);
		uart_print("T01: 0x03\r\n");
	}
}

static void task3(){
	while(1){
		os_event_wait_any(0, 0xff);
		uart_print("T_ANY: 0xff\r\n");
	}
}


void test11(){
	char c;

	os_event_init(0);

	os_task_create(task0, 0, 1, 1024, 0);
	os_task_create(task1, 0, 1, 1024, 0);
	os_task_create(task2, 0, 1, 1024, 0);
	os_task_create(task3, 0, 1, 1024, 0);

	while(1){
		uart_print("\r\n>");
		uart_getc(&c);

		switch(c){
		case '0':
			os_event_set(0, 0x01);
			break;
		case '1':
			os_event_set(0, 0x02);
			break;
		case '2':
			os_event_set(0, 0x04);
			break;
		case '3':
			os_event_set(0, 0x08);
			break;
		case '4':
			os_event_set(0, 0x10);
			break;
		default:
			uart_print(" Illegal input.\r\n");
			break;
		}
	}
}
