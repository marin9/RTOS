#include "stack.h"


void stack_init(stack_t *s){
	s->count=0;
	s->first=0;
}

void stack_push(stack_t *s, sitem_t *i){
	i->next=s->first;
	s->first=i;
	++(s->count);
}

sitem_t* stack_pop(stack_t *s){
	if(s->first){
		sitem_t *t=s->first;
		--(s->count);
		s->first=s->first->next;
		return t;
	}else{
		return 0;
	}
}

int stack_empty(stack_t *s){
	return !(s->count);
}

int stack_size(stack_t *s){
	return s->count;
}
