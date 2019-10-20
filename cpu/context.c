#include "cpu.h"

void context_create(void *ctx, void *fn, void *args, void *reap){
	context_t *c=(context_t*)ctx;
	c->cpsr=CPSR_MODE_SYS;
	c->r0=(uint)args;	
  	c->lr=(uint)reap;
  	c->pc=(uint)fn;
}
