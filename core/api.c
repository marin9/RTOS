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
	ret=task_term(id);

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
	return task_getname(id, name);
}

int os_task_getstat(uint id){
	return task_getstat(id);
}

int os_task_getid(){
	return task_getid();
}

void os_task_exit(){
	task_exit();
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

int os_task_set_prio(uint id, uint p){
	int ret;
	uint sr=sys_entry();
	ret=task_set_prio(id, p);
	sys_exit(sr);
	return ret;
}

int os_task_get_prio(uint id){
	return task_get_prio(id);
}

int os_task_sleep(uint ms){
	int ret;
	uint sr=sys_entry();
	ret=task_sleep(ms);
	sys_exit(sr);
	return ret;
}

int os_task_signal(uint id){
	int ret;
	uint sr=sys_entry();
	ret=task_signal(id);
	sys_exit(sr);
	return ret;
}
