#pragma once

typedef struct{
	int top;
	int isize;
	int nsize;
	void *buff;
} stack_t;


void stack_init(stack_t *s, void *buf, int size, int n);
int stack_push(stack_t *s, void *data);
int stack_pop(stack_t *s, void *data);
int stack_peek(stack_t *s, void *data);
int stack_empty(stack_t *s);
int stack_full(stack_t *s);

