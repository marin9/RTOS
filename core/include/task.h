#pragma once
#include "types.h"
#include "param.h"

#define TASK_DORMANT	0
#define TASK_READY		1
#define TASK_SUSPEND 	2


typedef struct task_t{
	uint *sp;
	uint id;
	uint prio;
	uint status;
	char name[NAME_LEN];
	struct task_t *next;
	struct task_t *prev;
} task_t;

typedef struct{
	task_t *first;
	task_t *last;
} task_queue_t;


void task_queue_init(task_queue_t *q);
void task_enqueue(task_queue_t *q, task_t *t);
void task_remove(task_queue_t *q, task_t *t);
task_t* task_dequeue(task_queue_t *q);

void task_init();
void task_sched_start();
int task_create(func fn, void *args, uint prio, uint stack, char *name);
int task_getname(uint id, char *name);
int task_getstat(uint id);
int task_term(uint id);
int task_getid();
void task_yield();
void task_exit();
int task_suspend(uint id);
int task_resume(uint id);
int task_set_prio(uint id, uint p);
int task_get_prio(uint id);
void task_sleep(uint ms);
