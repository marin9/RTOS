#include "queue.h"

void queue_init(queue_t *q){
	q->first=0;
	q->last=0;
}

void queue_remove(queue_t *q, node_t *n){
	if(q->first==n){
		queue_pop(q);
	}else if(q->last==n){
		q->last=n->prev;
		q->last->next=0;
		n->next=0;
		n->prev=0;
	}else{
		n->prev->next=n->next;
		n->next->prev=n->prev;
		n->next=0;
		n->prev=0;
	}
}

void queue_push(queue_t *q, node_t *n){
	if(q->last==0){
		q->first=n;
		q->last=n;
		n->next=0;
		n->prev=0;
	}else{
		n->next=0;
		n->prev=q->last;
		q->last->next=n;
		q->last=n;
	}
}

node_t* queue_pop(queue_t *q){
	node_t *t=q->first;

	if(t==0){
		return 0;
	}	

	q->first=q->first->next;
	if(q->first!=0){
		q->first->prev=0;
	}else{
		q->last=0;
	}
	t->next=0;
	t->prev=0;
	return t;
}

