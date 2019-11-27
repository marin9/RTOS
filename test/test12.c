#include "api.h"
#include "time.h"
#include "device.h"
#include "string.h"

//	TEST:
//	mbox_send
//	mbox_recv

#define SEND_DELAY	100
#define RECV_DELAY	1000



static void task0(){
	char buff[4];
	buff[0]=48;
	buff[1]='\r';
	buff[2]='\n';
	buff[3]=0;

	while(1){
		os_mbox_send(0, buff);
		os_task_sleep(SEND_DELAY);
		++buff[0];
	}
}

static void task1(){
	char buff[4];

	while(1){
		os_mbox_recv(0, buff);
		uart_print("A: ");
		uart_print(buff);
		os_task_sleep(RECV_DELAY);
	}
}

static void task2(){
	char buff[4];

	while(1){
		os_mbox_recv(0, buff);
		uart_print("B: ");
		uart_print(buff);
		os_task_sleep(RECV_DELAY);
	}
}


void test12(){
	os_mbox_init(0);
	time_delay(6000000);

	os_task_create(task0, 0, 1, 1024, 0);
	time_delay(30000);
	os_task_create(task1, 0, 1, 1024, 0);
	time_delay(30000);
	os_task_create(task2, 0, 1, 1024, 0);
}
