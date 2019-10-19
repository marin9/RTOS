#include "cpu.h"

void context_create(void *ctx, void *fn, void *args, void *reap){
	context_t *c=(context_t*)ctx;
	c->cpsr=0xdf;
	c->r0=(uint)args;
  	c->pc=(uint)fn;
  	c->lr=(uint)reap;
}
