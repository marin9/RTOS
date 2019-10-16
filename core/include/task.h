#pragma once
#include "types.h"


typedef struct{
	uint *sp;
	uint id;
	uint prio;
	uint status;
	char name[NAMELEN];
	struct task_t *next;
	struct task_t *prev;
} task_t;

typedef struct{
	task_t *first;
	task_t *last;
} task_queue_t;



void task_queue_init(task_queue_t *q){
	q->first=0;
	q->last=0;
}

void task_enqueue(task_queue_t *q, task_t *t){
	if(q->first==0){
		t->next=0;
		t->prev=0;

		q->first=t;
		q->last=t;
	}else{
		t->next=0;
		t->prev=q->last;
		q->flast->next=t;
		q->last=t;
	}
}

task_t* task_dequeue(task_queue_t *q){
	task_t *tmp=q->first;

	if(!tmp){
		return 0;
	}

	q->first=tmp->next;

	if(q->first)
		q->first->prev=0;
	else
		q->last=0;

	if(q->first)

	tmp->next=0;
	tmp->prev=0;
	return tmp;
}

void task_remove(task_queue_t *q, task_t *t){







}
