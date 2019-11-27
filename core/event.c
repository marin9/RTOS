#include "types.h"
#include "errno.h"
#include "task.h"


typedef struct{
	task_queue_t wait_q;
} event_t;

static event_t event[EVENT_COUNT];


int event_init(uint id){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}
	task_queue_init(&event[id].wait_q);
	return 0;
}

uint event_get(){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}
	return task[id].event_flags;
}

int event_clr(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	event[id].current_flags &= (~f);
	return 0;
}

int event_set(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	event[id].current_flags |= f;
	task_release_all(&event[id].wait_q);
	return 0;
}

int event_wait_all(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	uint current=event[id].current_flags;

	while((f&current) == f){
		task_block(&event[id].wait_q, TASK_BLOCKEVENT);
	}
	return 0;
}

int event_wait_any(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	uint current=event[id].current_flags;

	while(f&current){
		task_block(&event[id].wait_q, TASK_BLOCKEVENT);
	}
	return 0;
}

int event_try_all(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	uint current=event[id].current_flags;

	if((f&current) == f)
		return 1;
	else
		return 0;
}

int event_try_any(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	uint current=event[id].current_flags;

	if(f&current)
		return 1;
	else
		return 0;
}
