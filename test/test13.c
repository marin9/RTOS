#include "api.h"
#include "time.h"
#include "device.h"

//	TEST:
//	cond_wait
//	cond_signal

static int sticks[5];
static char status[8];


static void philosopher(void *args){
	int phid=(int)((int*)args);
	int phid_left=phid-1;
	int phid_right=phid+1;

	int stick_left=phid;
	int stick_right=phid+1;

	if(stick_right >= 5){
		stick_right=0;
	}

	if(phid_left < 0){
		phid_left=4;
	}

	if(phid_right >= 5){
		phid_right=0;
	}

	while(1){
		// think
		status[phid]='m';
		uart_print(status);
		os_task_sleep(1000);

		// get sticks
		os_mux_lock(0);
		while(!sticks[stick_left] || !sticks[stick_right]){
			os_cond_wait(phid, 0);
		}
		sticks[stick_left]=0;
		sticks[stick_right]=0;
		os_mux_unlock(0);

		// eat
		status[phid]='E';
		uart_print(status);
		os_task_sleep(1000);

		// release sticks
		os_mux_lock(0);
		sticks[stick_left]=1;
		sticks[stick_right]=1;
		os_cond_signal(phid_left);
		os_cond_signal(phid_right);
		os_mux_unlock(0);
	}
}



void test13(){
	os_mux_init(0);
	os_cond_init(0);
	os_cond_init(1);
	os_cond_init(2);
	os_cond_init(3);
	os_cond_init(4);

	status[0]='-';
	status[1]='-';
	status[2]='-';
	status[3]='-';
	status[4]='-';
	status[5]='\r';
	status[6]='\n';
	status[7]='\0';

	int i;
	for(i=0;i<5;++i){
		sticks[i]=1;
	}


	os_task_create(philosopher, (void*)0, 1, 1024, 0);
	os_task_sleep(100);
	os_task_create(philosopher, (void*)1, 1, 1024, 0);
	os_task_sleep(100);
	os_task_create(philosopher, (void*)2, 1, 1024, 0);
	os_task_sleep(100);
	os_task_create(philosopher, (void*)3, 1, 1024, 0);
	os_task_sleep(100);
	os_task_create(philosopher, (void*)4, 1, 1024, 0);
}
