#pragma once
#include "types.h"

void halt();
uint interrupts_enable();
uint interrupts_disable();
void context_switch(void *c1, void *c2);
