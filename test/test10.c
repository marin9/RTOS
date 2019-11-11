#include "api.h"
#include "time.h"
#include "string.h"
#include "device.h"

//	TEST:
//	semaphore 2
//	producer and consumer

#define CONSUMERS	2
#define PRODUCERS	3
#define BUFF_SIZE	5

#define SEM_EMPTY	0
#define SEM_FULL	1
#define SEM_CRITIC1	2
#define SEM_CRITIC2	3


static int n;
static int in, out;
static int buffer[BUFF_SIZE];


static void printf(char *f, ...){
	char buff[64];
	vssprintf(buff, &f);
	uart_print(buff);
}


static void consumers(void *args){
	while(1){
		os_sem_take(SEM_FULL);
		os_sem_take(SEM_CRITIC1);

		printf("Consumer: %d, Data: %d\r\n",
				(int)args, buffer[out]);

		out += 1;
		if(out>=BUFF_SIZE)
			out=0;

		os_sem_give(SEM_CRITIC1);
		os_sem_give(SEM_EMPTY);
		os_task_sleep(1000);
	}
}

static void producers(void *args){
	while(1){
		os_sem_take(SEM_EMPTY);
		os_sem_take(SEM_CRITIC2);

		printf("Produces: %d, Data: %d\r\n",
				(int)args, buffer[in]);

		in += 1;
		if(in>=BUFF_SIZE)
			in=0;

		os_sem_give(SEM_CRITIC2);
		os_sem_give(SEM_FULL);
		os_task_sleep(1000);
	}
}


void test10(){
	int i;
	time_delay(5000000);
	uart_print("Start\r\n");

	n=48;
	in=out=0;

	os_sem_init(SEM_EMPTY, BUFF_SIZE);
	os_sem_init(SEM_FULL, 0);
	os_sem_init(SEM_CRITIC1, 1);
	os_sem_init(SEM_CRITIC2, 1);

	for(i=0;i<CONSUMERS;++i)
		os_task_create(consumers, (void*)(i+1), 1, 1024, 0);

	for(i=0;i<PRODUCERS;++i)
		os_task_create(producers, (void*)(i+1), 1, 1024, 0);

}
