#pragma once
#include "types.h"

void timers_init();
void tmr_init(uint id, uint start, uint period, void (*handler)());
void tmr_start(uint id);
void tmr_stop(uint id);
uint tmr_value(uint id);
