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

