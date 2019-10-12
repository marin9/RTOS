#include "cpu.h"
#include "rpi.h"
#include "types.h"
#include "device.h"
#include "interrupt.h"


int len;
char buffer[32];


void fn(){
	uart_print("M\r\n");

	timer_set(1000000);
}


void main(){
	uart_init();
	pic_init();
	interrupt_init();
	timer_init();

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
	}

}


