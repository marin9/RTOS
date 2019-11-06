#pragma once
#include "task.h"
#include "types.h"

typedef struct{
	task_t *first;
	task_t *last;
} task_queue_t;


void task_queue_init(task_queue_t *q);
void task_enqueue(task_queue_t *q, task_t *t);
void task_remove(task_queue_t *q, task_t *t);
task_t* task_dequeue(task_queue_t *q);
task_t* task_peek(task_queue_t *q);
void task_enqueue_sleep(task_queue_t *q, task_t *t, uint ticks);
void task_dequeue_sleep(task_queue_t *q, task_t *t);
