#include "types.h"
#include "errno.h"
#include "mutex.h"
#include "param.h"
#include "task.h"


typedef struct{
	task_queue_t wait_q;
} cond_t;

static cond_t cond[COND_COUNT];



int cond_init(uint id){
	if(id>=COND_COUNT){
		return -ERR_NORES;
	}
	task_queue_init(&cond[id].wait_q);
	return 0;
}

int cond_wait(uint id, uint mx_id){
	if(id>=COND_COUNT || mx_id>=MUX_COUNT){
		return -ERR_NORES;
	}

	mux_unlock(mx_id);
	task_block(&cond[id].wait_q, TASK_BLOCKCOND);
	mux_lock(mx_id);
	return 0;
}

int cond_signal(uint id){
	if(id>=COND_COUNT){
		return -ERR_NORES;
	}

	return task_release(&cond[id].wait_q);
}

int cond_broadcast(uint id){
	while(!cond_signal(id));
	return 0;
}
