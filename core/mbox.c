#include "types.h"
#include "errno.h"
#include "param.h"
#include "string.h"
#include "task.h"


typedef struct{
	int count;
	int send_x;
	int recv_x;
	task_queue_t send_wait;
	task_queue_t recv_wait;
	char data[MBOX_SIZE][MBOX_ITEM_LEN];
} mbox_t;

static mbox_t mbox[MBOX_COUNT];



int mbox_init(uint id){
	if(id>=MBOX_COUNT){
		return -ERR_NORES;
	}

	mbox[id].count=0;
	mbox[id].send_x=0;
	mbox[id].recv_x=0;
	task_queue_init(&mbox[id].send_wait);
	task_queue_init(&mbox[id].recv_wait);
	return 0;
}

int mbox_send(uint id, void *msg){
	if(id>=MBOX_COUNT){
		return -ERR_NORES;
	}

	while(mbox[id].count >= MBOX_SIZE){
		task_block(&mbox[id].send_wait, TASK_BLOCKSEND);
	}

	int send_x=mbox[id].send_x;
	memcpy(mbox[id].data[send_x], msg, MBOX_ITEM_LEN);
	mbox[id].count += 1;

	mbox[id].send_x += 1;
	if(mbox[id].send_x >= MBOX_SIZE){
		mbox[id].send_x=0;
	}

	task_release(&mbox[id].recv_wait);
	return 0;
}

int mbox_recv(uint id, void *msg){
	if(id>=MBOX_COUNT){
		return -ERR_NORES;
	}

	while(!mbox[id].count){
		task_block(&mbox[id].recv_wait, TASK_BLOCKRECV);
	}

	int recv_x=mbox[id].recv_x;
	memcpy(msg, mbox[id].data[recv_x], MBOX_ITEM_LEN);
	mbox[id].count -= 1;

	mbox[id].recv_x += 1;
	if(mbox[id].recv_x >= MBOX_SIZE){
		mbox[id].recv_x=0;
	}

	task_release(&mbox[id].send_wait);
	return 0;
}

int mbox_try_send(uint id, void *msg){
	if(id>=MBOX_COUNT){
		return -ERR_NORES;
	}

	if(mbox[id].count >= MBOX_SIZE){
		return 1;
	}

	int send_x=mbox[id].send_x;
	memcpy(mbox[id].data[send_x], msg, MBOX_ITEM_LEN);
	mbox[id].count += 1;

	mbox[id].send_x += 1;
	if(mbox[id].send_x >= MBOX_SIZE){
		mbox[id].send_x=0;
	}

	task_release(&mbox[id].recv_wait);
	return 0;
}

int mbox_try_recv(uint id, void *msg){
	if(id>=MBOX_COUNT){
		return -ERR_NORES;
	}

	while(!mbox[id].count){
		return 1;
	}

	int recv_x=mbox[id].recv_x;
	memcpy(msg, mbox[id].data[recv_x], MBOX_ITEM_LEN);
	mbox[id].count -= 1;

	mbox[id].recv_x += 1;
	if(mbox[id].recv_x >= MBOX_SIZE){
		mbox[id].recv_x=0;
	}
	
	task_release(&mbox[id].send_wait);
	return 0;
}
