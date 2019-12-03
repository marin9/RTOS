#include "cpu.h"
#include "rpi.h"
#include "task.h"
#include "time.h"
#include "test.h"
#include "prog.h"
#include "types.h"
#include "mpool.h"
#include "timers.h"
#include "string.h"
#include "device.h"
#include "interrupt.h"


void main(){
	uart_init();
	pic_init();
	interrupt_init();
	timer_init();
	task_init();
	time_init();
	timers_init();

	task_create(shell, 0, PRIO_DEFAULT, STACK_DEFAULT, "main");
	task_start();
}
