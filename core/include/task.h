#pragma once
#include "param.h"
#include "types.h"
#include "taskq.h"


void task_init();
void task_start();
void task_tick();

int task_create(func fn, void *args, uint prio, uint stack, char *name);
void task_yield();
void task_exit(int ret);
int task_kill(uint id);
void task_sleep(uint ticks);
int task_wakeup(uint id);
void task_block(task_queue_t *q, uint stat);
int task_release(task_queue_t *q);
void task_release_all(task_queue_t *q);
int task_get_id();
int task_get_name(uint id, char *name);
int task_get_status(uint id);
int task_get_prio(uint id);
int task_set_prio(uint p);
int task_suspend(uint id);
int task_resume(uint id);
int task_join(uint id, int *ret);
task_t* task_get_descriptor();
