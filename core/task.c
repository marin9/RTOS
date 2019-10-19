#include "cpu.h"
#include "task.h"
#include "param.h"
#include "types.h"
#include "string.h"

static char idle_stack[IDLE_STACK] __attribute__((aligned(8)));

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
		q->last->next=t;
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



static void task_idle(){
	while(1){
		uart_print("IDLE\r\n");
		task_yield();
	}
}

static void task_reap(){
	interrupts_disable();
	task[active_task].status=TASK_DORMANT;
	task_yield();
}


void task_init(){
	int i;
	for(i=0;i<PRIO_COUNT;++i){
		task_queue_init(&queue_ready[i]);
	}
	for(i=0;i<TASK_COUNT;++i){
		task[i].status=0;
	}
	active_task=0;
	task_create(task_idle, 0, 0, idle_stack, IDLE_STACK, "idle");
}

void task_sched_start(){
	int i;
	task_t *new;

	for(i=PRIO_COUNT-1;i>=0;--i){
		new=task_dequeue(&queue_ready[i]);
		if(new){
			break;
		}
	}
	
	active_task=new->id;

	context_switch(0, new);
}

int task_create(func fn, void *args, uint prio, void *stack, uint size, char *name){
	if(!fn){
		return -1;
	}

	interrupts_disable();

	int i;
	for(i=0;i<TASK_COUNT;++i){
		if(!task[i].status){
			if(i>=TASK_COUNT){
				interrupts_enable();
				return -2;
			}else{
				break;
			}
		}
	}

	task[i].id=i;
	task[i].prio=prio;
	task[i].sp=(uint*)((char*)stack+size-4);
	task[i].sp-=sizeof(context_t);
	task[i].status=TASK_READY;
	if(name){
		strcpy(task[i].name, name);
	}else{
		strcpy(task[i].name, "no_name");
	}

	context_t *ctx=(context_t*)task[i].sp;
	context_create(ctx, fn, args, task_reap);

	task_enqueue(&queue_ready[prio], &task[i]);
	interrupts_enable();
	return i;
}

void task_yield(){
	int i;
	task_t *old;
	task_t *new;

	old=&task[active_task];
	task_enqueue(&queue_ready[old->prio], old);

	for(i=PRIO_COUNT-1;i>=0;--i){
		new=task_dequeue(&queue_ready[i]);
		if(new){
			break;
		}
	}
	active_task=new->id;
	context_switch(old, new); 	
}
