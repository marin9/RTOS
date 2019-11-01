#pragma once
#include "types.h"

int sem_init(uint id, uint v);
int sem_take(uint id);
int sem_give(uint id);
int sem_try(uint id);
