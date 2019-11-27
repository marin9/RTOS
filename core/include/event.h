#pragma once
#include "types.h"

int event_init(uint id);
uint event_get(uint id);
int event_clr(uint id, uint f);
int event_set(uint id, uint f);
int event_wait_all(uint id, uint f);
int event_wait_any(uint id, uint f);
int event_try_all(uint id, uint f);
int event_try_any(uint id, uint f);
