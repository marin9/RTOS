#pragma once
#include "task.h"
#include "types.h"


int os_task_create(func fn, void *args, uint prio, uint stack, char *name);
int os_task_term(uint id);
void os_task_yield();
