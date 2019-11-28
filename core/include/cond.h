#pragma once
#include "types.h"

int cond_init(uint id);
int cond_wait(uint id, uint mx_id);
int cond_signal(uint id);
int cond_broadcast(uint id);
