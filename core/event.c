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

int event_set(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	task_t *tmp=task_peek(&event[id].wait_q);

	while(tmp){
		tmp->event_flags |= f;
		tmp=tmp->next;
	}

	task_release_all(&event[id].wait_q);
	return 0;
}

int event_wait_all(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	task_t *tmp=task_get_descriptor();

	uint current=tmp->event_flags=0;

	while((f&current) != f){
		task_block(&event[id].wait_q, TASK_BLOCKEVENT);
		current=tmp->event_flags;
	}
	return 0;
}

int event_wait_any(uint id, uint f){
	if(id>=EVENT_COUNT){
		return -ERR_NORES;
	}

	task_t *tmp=task_get_descriptor();

	uint current=tmp->event_flags=0;

	while(!(f&current)){
		task_block(&event[id].wait_q, TASK_BLOCKEVENT);
		current=tmp->event_flags;
	}
	return 0;
}
