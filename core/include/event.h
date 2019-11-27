#pragma once
#include "types.h"

int event_init(uint id);
int event_set(uint id, uint f);
int event_wait_all(uint id, uint f);
int event_wait_any(uint id, uint f);
