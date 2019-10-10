#pragma once
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
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
} list_t;


void list_init(list_t *l);
void list_add_first(list_t *l, node_t *n);
void list_add_last(list_t *l, node_t *n);
node_t* list_remove(list_t *l, node_t *n);
node_t* list_remove_first(list_t *l);
node_t* list_remove_last(list_t *l);

