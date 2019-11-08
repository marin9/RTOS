#include "sem.h"
#include "cpu.h"
#include "task.h"


int os_task_create(func fn, void *args, uint prio, uint stack, char *name){
	int ret;
	uint sr;

	sr=sys_entry();
	ret=task_create(fn, args, prio, stack, name);

	sys_exit(sr);
	return ret;
}

int os_task_term(uint id){
	int ret;
	uint sr;

	sr=sys_entry();
	ret=task_kill(id);

	sys_exit(sr);
	return ret;
}

void os_task_yield(){
	uint sr;
	sr=sys_entry();
	task_yield();
	sys_exit(sr);
}

int os_task_getname(uint id, char *name){
	return task_get_name(id, name);
}

int os_task_getstat(uint id){
	return task_get_status(id);
}

int os_task_getid(){
	return task_get_id();
}

void os_task_exit(int ret){
	task_exit(ret);
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

int os_task_set_prio(uint p){
	int ret;
	uint sr=sys_entry();
	ret=task_set_prio(p);
	sys_exit(sr);
	return ret;
}

int os_task_get_prio(uint id){
	return task_get_prio(id);
}

void os_task_sleep(uint ms){
	uint sr=sys_entry();
	task_sleep(ms);
	sys_exit(sr);
}

int os_task_signal(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_wakeup(id);
	sys_exit(sr);
	return ret;
}
/*
int os_sem_init(uint id, uint v){
	int ret;
	uint sr=sys_entry();
	ret=sem_init(id, v);
	sys_exit(sr);
	return ret;
}

int os_sem_take(uint id){
	int ret;
	uint sr=sys_entry();
	ret=sem_take(id);
	sys_exit(sr);
	return ret;
}

int os_sem_give(uint id){
	int ret;
	uint sr=sys_entry();
	ret=sem_give(id);
	sys_exit(sr);
	return ret;
}

int os_sem_try(uint id){
	int ret;
	uint sr=sys_entry();
	ret=sem_try(id);
	sys_exit(sr);
	return ret;
}
*/