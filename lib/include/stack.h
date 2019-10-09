#pragma once

typedef struct sitem_t{
	struct sitem_t *next;
} sitem_t;

typedef struct{
	int count;
	sitem_t *first;
} stack_t;


void stack_init(stack_t *s);
void stack_push(stack_t *s, sitem_t *i);
sitem_t* stack_pop(stack_t *s);
int stack_empty(stack_t *s);
int stack_size(stack_t *s);
