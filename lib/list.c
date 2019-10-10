#include "list.h"

void list_init(list_t *l){
	l->first=0;
	l->last=0;
}

void list_add_first(list_t *l, node_t *n){
	if(l->last==0){
		l->first=n;
		l->last=n;
		n->next=0;
		n->prev=0;
	}else{
		n->next=l->first;
		n->prev=0;
		l->first->prev=n;
		l->first=n;
	}
}

void list_add_last(list_t *l, node_t *n){
	if(l->last==0){
		l->first=n;
		l->last=n;
		n->next=0;
		n->prev=0;
	}else{
		n->next=0;
		n->prev=l->last;
		l->last->next=n;
		l->last=n;
	}
}

node_t* list_remove(list_t *l, node_t *n){
	if(l->first==n){
		l->first=n->next;
		if(l->first){
			l->first->prev=0;
		}else{
			l->last=0;
		}
		n->next=0;
		n->prev=0;
	}else if(l->last==n){
		l->last=n->prev;
		l->last->next=0;
		n->next=0;
		n->prev=0;
	}else{
		n->prev->next=n->next;
		n->next->prev=n->prev;
		n->next=0;
		n->prev=0;
	}
	return n;
}

node_t* list_remove_first(list_t *q){
	return list_remove(q, q->first);
}

node_t* list_remove_last(list_t *q){
	return list_remove(q, q->last);
}


