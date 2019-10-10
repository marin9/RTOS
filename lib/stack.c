#include "stack.h"
#include <string.h>


void stack_init(stack_t *s, void *buf, int size, int n){
	s->buff=buf;
	s->isize=size;
	s->nsize=n;
	s->top=0;
}

int stack_push(stack_t *s, void *data){
	if(s->top>=s->nsize){
		return 0;
	}

	char *dst=(char*)s->buff;
	char *src=(char*)data;

	memcpy(dst+s->top*s->isize, src, s->isize);
	++(s->top);
	return 1;
}

int stack_pop(stack_t *s, void *data){
	if(!s->top){
		return 0;
	}

	char *src=(char*)s->buff;
	char *dst=(char*)data;

	--(s->top);
	memcpy(dst, src+s->top*s->isize, s->isize);	
	return 1;
}

int stack_peek(stack_t *s, void *data){
	if(!s->top){
		return 0;
	}

	char *src=(char*)s->buff;
	char *dst=(char*)data;

	memcpy(dst, src+(s->top-1)*s->isize, s->isize);	
	return 1;
}

int stack_empty(stack_t *s){
	return s->top==0;
}

int stack_full(stack_t *s){
	return s->top>=s->nsize;
}

