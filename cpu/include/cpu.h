#pragma once
#include "types.h"

void context_switch(void *c1, void *c2);
uint interrupts_enable();
uint interrupts_disable();
void halt();

