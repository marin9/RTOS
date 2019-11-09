#include "types.h"
#include "errno.h"
#include "task.h"


typedef struct{
	int owner;
	uint locked;
	task_queue_t wait_q;
} mux_t;

static mux_t mux[MUX_COUNT];


int mux_init(uint id){
	if(id>=MUX_COUNT){
		return -ERR_NORES;
	}

	mux[id].locked=0;
	mux[id].owner=-1;
	task_queue_init(&mux[id].wait_q);
	return 0;
}

int mux_lock(uint id){
	if(id>=MUX_COUNT){
		return -ERR_NORES;
	}

	if(mux[id].locked == 0){
		mux[id].locked=1;
	}else{
		task_block(&mux[id].wait_q, TASK_BLOCKMUX);
	}

	mux[id].owner=task_get_id();
	return 0;
}

int mux_unlock(uint id){
	if(id>=MUX_COUNT){
		return -ERR_NORES;
	}

	if(mux[id].owner != task_get_id()){
		return -ERR_ILGSTAT;
	}

	if(!task_peek(&mux[id].wait_q)){
		mux[id].locked=0;
	}else{
		task_release(&mux[id].wait_q);
		task_yield();
	}
	return 0;
}

int mux_trylock(uint id){
	if(id>=MUX_COUNT){
		return -ERR_NORES;
	}

	if(mux[id].locked == 0){
		mux[id].locked=1;
	}else{
		return 1;
	}
	
	mux[id].owner=task_get_id();
	return 0;
}
