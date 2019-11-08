#pragma once
#include "task.h"
#include "types.h"

int os_task_create(func fn, void *args, uint prio, uint stack, char *name);
void os_task_yield();
void os_task_exit(int ret);
void os_task_sleep(uint ticks);
int os_task_wakeup(uint id);
int os_task_kill(uint id);
int os_task_get_id();
int os_task_get_name(uint id, char *name);
int os_task_get_status(uint id);
int os_task_get_prio(uint id);
int os_task_set_prio(uint p);
int os_task_suspend(uint id);
int os_task_resume(uint id);
int os_task_joint(uint id);
