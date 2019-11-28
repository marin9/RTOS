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
int os_task_join(uint id, int *ret);

int os_sem_init(uint id, uint v);
int os_sem_take(uint id);
int os_sem_give(uint id);
int os_sem_try(uint id);

int os_mux_init(uint id);
int os_mux_lock(uint id);
int os_mux_unlock(uint id);
int os_mux_trylock(uint id);

int os_cond_init(uint id);
int os_cond_wait(uint id, uint mx_id);
int os_cond_signal(uint id);
int os_cond_broadcast(uint id);

int os_event_init(uint id);
int os_event_set(uint id, uint f);
int os_event_wait_all(uint id, uint f);
int os_event_wait_any(uint id, uint f);

int os_mbox_init(uint id);
int os_mbox_send(uint id, void *msg);
int os_mbox_recv(uint id, void *msg);
int os_mbox_try_send(uint id, void *msg);
int os_mbox_try_recv(uint id, void *msg);
