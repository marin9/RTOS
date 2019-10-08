#pragma once

#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})


typedef struct node_t{
	struct node_t *next;
	struct node_t *prev;
} node_t;

typedef struct{
	node_t *first;
	node_t *last;
} queue_t;


void queue_init(queue_t *q);
void queue_remove(queue_t *q, node_t *n);
void queue_push(queue_t *q, node_t *n);
node_t* queue_pop(queue_t *q);

