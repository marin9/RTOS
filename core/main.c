#include "cpu.h"
#include "rpi.h"
#include "task.h"
#include "types.h"
#include "device.h"
#include "interrupt.h"

/*
int len;
char buffer[32];


void fn(){
	uart_print("M\r\n");

	timer_set(1000000);
}*/

char main_stack[1024] __attribute__((aligned(8)));

void main_task(){
	while(1){
		uart_print("MAIN\r\n");
		task_yield();
	}
}


void main(){
	uart_init();
	pic_init();
	interrupt_init();
	timer_init();
/*
	gpio_open(47, GP_OUT);
	gpio_write(47, 1);


	pic_enable(SYSTMR1_IRQ);
	interrupt_register(SYSTMR1_IRQ, fn);
	timer_set(1000000);
	interrupts_enable();


	while(1){
		len=0;
		while(len<10)
			len+=uart_read(0, buffer+len, 10-len);

		gpio_write(47, 0);
		uart_write(0, buffer, 10);
		timer_wait(1000000);
		gpio_write(47, 1);
	}*/


	timer_wait(5000000);
	uart_print("1\r\n");

	task_init();

	task_create(main_task, 0, 0, main_stack, 1024, "main");

	task_sched_start();
}


