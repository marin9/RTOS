#pragma once
#include "types.h"
#include "param.h"

#define TASK_DORMANT	0
#define TASK_READY		1
#define TASK_SUSPEND 	2
#define TASK_SLEEP 		3
#define TASK_BLOCKSEM	4


typedef struct task_t{
	uint *sp;
	uint id;
	uint prio;
	uint sleep;
	uint status;
	int retval;
	char name[NAME_LEN];
	struct task_t *next;
	struct task_t *prev;
} task_t;


void task_init();
void task_sched_start();
int task_create(func fn, void *args, uint prio, uint stack, char *name);
void task_exit();
void task_sleep(uint ticks);
int task_wakeup(uint id);
void task_block(task_queue_t *q, uint stat);
int task_release(task_queue_t *q);
void task_release_all(task_queue_t *q);

int task_getname(uint id, char *name);
int task_getstat(uint id);
int task_term(uint id);
int task_getid();
void task_yield();
int task_suspend(uint id);
int task_resume(uint id);
int task_set_prio(uint id, uint p);
int task_get_prio(uint id);
//void task_wait(task_queue_t *q, int stat);
//int task_wakeup(task_queue_t *q);
int task_wakeup_all(task_queue_t *q);
//int task_sleep(uint ms);
int task_signal(uint id);
