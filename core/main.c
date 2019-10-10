#include "cpu.h"
#include "device.h"
#include "types.h"
int len;
char buffer[128];


void main(){
	uart_init();

	while(1){
		len=0;
		while(len<10)
			len+=uart_read(0, buffer+len, 10-len);

		uart_write(0, buffer, 10);
	}

}


