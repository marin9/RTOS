#pragma once
#include "types.h"

typedef struct{
	uint r0;
	uint r1;
	uint r2;
	uint r3;
	uint r4;
	uint r5;
	uint r6;
	uint r7;
	uint r8;
	uint r9;
	uint r10;
	uint r11;
	uint cpsr;
	uint lr;
	uint pc;
} context_t;

void halt();
uint interrupts_enable();
uint interrupts_disable();
void context_switch(void *c1, void *c2);
void context_create(void *ctx, void *fn, void *args, void *reap);
