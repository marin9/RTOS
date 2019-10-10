#pragma once

typedef struct{
	int first;
	int last;
	int count;
	int isize;
	int nsize;
	void *buff;
} queue_t;

void queue_init(queue_t *q, void *buf, int size, int n);
int queue_enqueue(queue_t *q, void *data);
int queue_dequeue(queue_t *q, void *data);
int queue_peek(queue_t *q, void *data);
int queue_empty(queue_t *q);
int queue_full(queue_t *q);

