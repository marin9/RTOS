#pragma once
#include "types.h"

void timer_init();
void timer_set(uint us);
uint timer_get();

void pic_init();
void pic_enable(uint irqn);
void pic_disable(uint irqn);
uint pic_ispending(uint irqn);

void uart_init();
int uart_read(int unit, void* buffer, int size);
int uart_write(int unit, void* buffer, int size);
