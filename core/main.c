#include "cpu.h"
#include "rpi.h"
#include "task.h"
#include "time.h"
#include "types.h"
#include "mpool.h"
#include "string.h"
#include "device.h"
#include "interrupt.h"


void test1();


void main(){
	uart_init();
	pic_init();
	interrupt_init();
	timer_init();
	task_init();
	time_init();

	task_create(test1, 0, 0, 1024, "main");
	task_sched_start();
}
