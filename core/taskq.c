#include "taskq.h"


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
		q->last->next=t;
		q->last=t;
	}
}

task_t* task_peek(task_queue_t *q){
	return q->first;
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
	if(q->first==t){
		task_dequeue(q);
	}else if(q->last==t){
		q->last=t->prev;
		q->last->next=0;
	}else{
		t->prev->next=t->next;
		t->next->prev=t->prev;
	}
	t->next=0;
	t->prev=0;
}

void task_enqueue_sleep(task_queue_t *q, task_t *t, uint ticks){
	task_t *tmp;
	task_t *prev;

	t->sleep=ticks;

	if(!q->first){
		q->first=t;
		q->last=t;
		t->next=0;
		t->prev=0;
		return;
	}

	tmp=q->first;
	prev=0;

	while(tmp && (t->sleep >= tmp->sleep)){
		t->sleep -= tmp->sleep;
		prev=tmp;
		tmp=tmp->next;
	}

	if(!tmp){
		// add at end
		prev->next=t;
		t->prev=prev;
		t->next=0;

		q->last=t;
	}else{
		// insert and dec
		tmp->sleep -= t->sleep;

		if(prev){
			prev->next=t;
			tmp->prev=t;
			t->next=tmp;
			t->prev=prev;
		}else{
			// add first
			q->first=t;

			tmp->prev=t;
			t->next=tmp;
			t->prev=0;
		}
	}
}

void task_dequeue_sleep(task_queue_t *q, task_t *t){
	if(t==q->first){
		q->first=t->next;
		if(!q->first){
			q->first=0;
			q->last=0;
		}else{
			q->first->prev=0;
			q->first->sleep += t->sleep;
		}
	}else if(t==q->last){
		q->last=t->prev;
		q->last->next=0;
	}else{
		task_t *next=t->next;
		task_t *prev=t->prev;

		prev->next=next;
		next->prev=prev;

		next->sleep += t->sleep;
	}
	t->next=0;
	t->prev=0;
}
