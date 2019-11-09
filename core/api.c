#include "sem.h"
#include "cpu.h"
#include "task.h"
#include "mutex.h"


int os_task_create(func fn, void *args, uint prio, uint stack, char *name){
	int ret;
	uint sr;

	sr=sys_entry();
	ret=task_create(fn, args, prio, stack, name);

	sys_exit(sr);
	return ret;
}

void os_task_yield(){
	uint sr=sys_entry();
	task_yield();
	sys_exit(sr);
}

void os_task_exit(int ret){
	uint sr=sys_entry();
	task_exit(ret);
	sys_exit(sr);	
}

void os_task_sleep(uint ticks){
	uint sr=sys_entry();
	task_sleep(ticks);
	sys_exit(sr);
}

int os_task_wakeup(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_wakeup(id);
	sys_exit(sr);
	return ret;
}

int os_task_kill(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_kill(id);
	sys_exit(sr);
	return ret;
}

int os_task_get_id(){
	return task_get_id();
}

int os_task_get_name(uint id, char *name){
	int ret;
	uint sr=sys_entry();
	ret=task_get_name(id, name);
	sys_exit(sr);
	return ret;
}

int os_task_get_status(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_get_status(id);
	sys_exit(sr);
	return ret;
}

int os_task_get_prio(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_get_prio(id);
	sys_exit(sr);
	return ret;
}

int os_task_set_prio(uint p){
	int ret;
	uint sr=sys_entry();
	ret=task_set_prio(p);
	sys_exit(sr);
	return ret;
}

int os_task_suspend(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_suspend(id);
	sys_exit(sr);
	return ret;
}

int os_task_resume(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_resume(id);
	sys_exit(sr);
	return ret;
}

int os_task_join(uint id, int *ret){
	int r;
	uint sr=sys_entry();
	r=task_join(id, ret);
	sys_exit(sr);
	return r;
}


int os_sem_init(uint id, uint v){
	int r;
	uint sr=sys_entry();
	r=sem_init(id, v);
	sys_exit(sr);
	return r;
}

int os_sem_take(uint id){
	int r;
	uint sr=sys_entry();
	r=sem_take(id);
	sys_exit(sr);
	return r;
}

int os_sem_give(uint id){
	int r;
	uint sr=sys_entry();
	r=sem_give(id);
	sys_exit(sr);
	return r;
}

int os_sem_try(uint id){
	int r;
	uint sr=sys_entry();
	r=sem_try(id);
	sys_exit(sr);
	return r;
}


int os_mux_init(uint id){
	int r;
	uint sr=sys_entry();
	r=mux_init(id);
	sys_exit(sr);
	return r;
}

int os_mux_lock(uint id){
	int r;
	uint sr=sys_entry();
	r=mux_lock(id);
	sys_exit(sr);
	return r;
}

int os_mux_unlock(uint id){
	int r;
	uint sr=sys_entry();
	r=mux_unlock(id);
	sys_exit(sr);
	return r;
}

int os_mux_trylock(uint id){
	int r;
	uint sr=sys_entry();
	r=mux_trylock(id);
	sys_exit(sr);
	return r;
}
