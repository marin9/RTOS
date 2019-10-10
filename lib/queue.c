#include "queue.h"
#include <string.h>


void queue_init(queue_t *q, void *buf, int size, int n){
	q->first=0;
	q->last=0;
	q->count=0;
	q->buff=buf;
	q->isize=size;
	q->nsize=n;
}

int queue_enqueue(queue_t *q, void *data){
	if(q->count>=q->nsize){
		return 0;
	}

	char *src=(char*)data;
	char *dst=(char*)q->buff;

	memcpy(dst+q->last*q->isize, src, q->isize);

	++(q->count);
	++(q->last);
	if(q->last>=q->nsize){
		q->last=0;
	}
	return 1;
}

int queue_dequeue(queue_t *q, void *data){
	if(q->count==0){
		return 0;
	}

	char *src=(char*)q->buff;
	char *dst=(char*)data;

	memcpy(dst, src+q->first*q->isize, q->isize);

	--(q->count);
	++(q->first);
	if(q->first>=q->nsize){
		q->first=0;
	}
	return 1;
}

int queue_peek(queue_t *q, void *data){
	if(q->count==0){
		return 0;
	}

	char *src=(char*)q->buff;
	char *dst=(char*)data;

	memcpy(dst, src+q->first*q->isize, q->isize);
	return 1;
}

int queue_empty(queue_t *q){
	return q->count==0;
}

int queue_full(queue_t *q){
	return q->count>=q->nsize;
}

