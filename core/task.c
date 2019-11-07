#include "cpu.h"
#include "task.h"
#include "time.h"
#include "param.h"
#include "types.h"
#include "errno.h"
#include "taskq.h"
#include "string.h"

static char* stack_next;
static char stack[STACK_SPACE] \
	__attribute__((aligned(8)));

static uint sched_running;
static uint active_task;
static task_t task[TASK_COUNT];
static task_queue_t queue_ready[PRIO_COUNT];
static task_queue_t sleep_queue;



static void task_idle(){
	while(1);
}

static void task_reap(int ret){
	interrupts_disable();
	task[active_task].retval=ret;
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

	task_queue_init(&sleep_queue);
	stack_next=stack;
	active_task=0;
	sched_running=0;
	task_create(task_idle, 0, 0, 64, "idle");
}

void task_sched_start(){
	int i;
	task_t *new;

	sched_running=1;

	for(i=PRIO_COUNT-1;i>=0;--i){
		new=task_dequeue(&queue_ready[i]);
		if(new){
			break;
		}
	}
	
	active_task=new->id;
	context_switch(0, new);
}

void task_tick(){
	task_t *t;

	t=sleep_queue.first;
	t->sleep -= 1;
	if(t->sleep < 1){
		t->status=TASK_READY;
		task_dequeue_sleep(&sleep_queue, t);
	}
	task_yield();
}

int task_create(func fn, void *args, uint prio, uint stack, char *name){
	int i;

	if(!fn){
		return -ERR_ARGS;
	}

	for(i=0;i<TASK_COUNT;++i){
		if(!task[i].status){
			if(i>=TASK_COUNT){
				return -ERR_NORES;
			}else{
				break;
			}
		}
	}

	task[i].id=i;
	task[i].prio=prio;
	task[i].sp=(uint*)(stack_next+stack-4);
	task[i].sp-=sizeof(context_t);
	task[i].status=TASK_READY;

	if(name)
		strcpy(task[i].name, name);
	else
		strcpy(task[i].name, "no_name");

	stack_next+=stack;
	context_t *ctx=(context_t*)task[i].sp;
	context_create(ctx, fn, args, task_reap);

	task_enqueue(&queue_ready[prio], &task[i]);
	return i;
}

void task_yield(){
	int i;
	task_t *old;
	task_t *new;

	if(!sched_running){
		return;
	}

	task_wakeup_all(&sleep_queue);

	old=&task[active_task];
	if(old->status==TASK_READY)
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

void task_exit(int ret){
	task_reap(ret);
}

int task_kill(uint id){
	if(id==active_task){
		task_reap(-1);
	}

	if(id>TASK_COUNT){
		return -ERR_NOEXIST;
	}

	if(task[id].status!=TASK_DORMANT){
		task[id].status=TASK_DORMANT;
		task_remove(&queue_ready[task[id].prio], &task[id]);
		task_yield();
	}
	return 0;
}

void task_sleep(uint ticks){
	task_t *t=&task[active_task];
	t->status=TASK_SLEEP;
	task_enqueue_sleep(&sleep_queue, t, ticks);
	task_yield();
}

int task_wakeup(uint id){
	task_t *t=&task[id];

	if(t->status != TASK_SLEEP){
		return -ERR_ILSTAT;
	}
	t->status=TASK_READY;
	task_dequeue_sleep(&sleep_queue, t);
	task_yield();
	return 0;
}

void task_block(task_queue_t *q, uint stat){
	int i;
	task_t *old;
	task_t *new;

	old=&task[active_task];
	old->status=stat;
	task_enqueue(q, old);
	
	for(i=PRIO_COUNT-1;i>=0;--i){
		new=task_dequeue(&queue_ready[i]);
		if(new)
			break;
	}
	active_task=new->id;
	context_switch(old, new);
}

int task_release(task_queue_t *q){
	task_t *t=task_dequeue(q);
	if(!t){
		return -ERR_NORES;
	}

	task_enqueue(&queue_ready[t->prio], t);
	t->status=TASK_READY;
	return 0;
}

void task_release_all(task_queue_t *q){
	while(!task_release(q));
}

int task_get_id(){
	return active_task;
}

int task_get_name(uint id, char *name){
	if(id>TASK_COUNT){
		return -ERR_NOEXIST;
	}

	if(task[id].status==TASK_DORMANT){
		return -ERR_NORES;
	}

	strcpy(name, task[id].name);
	return 0;
}

int task_get_status(uint id){
	if(id>TASK_COUNT)
		return -ERR_NOEXIST;
	else
		return task[id].status;
}

int task_get_prio(uint id){
	if(id>TASK_COUNT){
		return -ERR_NOEXIST;
	}
	return task[id].prio;
}

int task_set_prio(uint p){
	if(p>=PRIO_COUNT){
		return -ERR_ARGS;
	}
	task[active_task].prio=p;
	task_yield();
	return 0;
}
