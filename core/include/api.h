#pragma once
#include "task.h"
#include "types.h"


int os_task_create(func fn, void *args, uint prio, uint stack, char *name);
int os_task_term(uint id);
int os_task_getname(uint id, char *name);
int os_task_getstat(uint id);
int os_task_getid();
void os_task_yield();
void os_task_exit();
int os_task_suspend(uint id);
int os_task_resume(uint id);
int os_task_set_prio(uint id, uint p);
int os_task_get_prio(uint id);
int os_task_sleep(uint ms);
int os_task_signal(uint id);
