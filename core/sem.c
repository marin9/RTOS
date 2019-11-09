#include "types.h"
#include "errno.h"
#include "task.h"


typedef struct{
	uint value;
	task_queue_t wait_q;
} sem_t;


static sem_t sem[SEM_COUNT];


int sem_init(uint id, uint v){
	if(id>=SEM_COUNT){
		return -ERR_NORES;
	}

	sem[id].value=v;
	task_queue_init(&sem[id].wait_q);
	return 0;
}

int sem_take(uint id){
	if(id>=SEM_COUNT){
		return -ERR_NORES;
	}

	if(sem[id].value > 0){
		sem[id].value -= 1;
	}else{
		task_block(&sem[id].wait_q, TASK_BLOCKSEM);
	}

	return 0;
}

int sem_give(uint id){
	if(id>=SEM_COUNT){
		return -ERR_NORES;
	}

	if(!task_peek(&sem[id].wait_q)){
		sem[id].value += 1;
	}else{
		task_release(&sem[id].wait_q);
		task_yield();
	}
	return 0;
}

int sem_try(uint id){
	if(id>=SEM_COUNT){
		return -ERR_NORES;
	}

	if(sem[id].value > 0){
		sem[id].value -= 1;
		return 0;
	}else{
		return 1;
	}
}
