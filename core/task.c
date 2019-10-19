#include "param.h"
#include "types.h"
#include "string.h"


static uint active_task;
static task_t task[TASK_COUNT];
static task_queue_t queue_ready[PRIO_COUNT];



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





int task_create(func fn, void *args, uint prio, void *stack, uint size, char *name){
	if(!fn){
		return -1;
	}

	interrupts_disable();

	int i;
	for(i=0;i<TASK_COUNT;++i){
		if(!task[i].status){
			if(i>=MAX_TASKS){
				interrupts_enable();
				return -2;
			}else{
				break;
			}
		}
	}

	task[i].id=i;
	task[i].prio=prio;
	task[i].sp=(uint*)((char)stack+size);
	task[i].sp-=sizeof(context_t);
	task[i].status=TASK_RUNNING;
	if(name){
		strcpy(task[i].name, name);
	}else{
		strcpy(task[i].name, "no_name");
	}

	context_t *ctx=(context_t*)task[i].sp;
	//context_create(ctx, fn, task_selfterminate);

	interrupts_enable();
	return i;
}

