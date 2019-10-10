#include "cpu.h"
#include "device.h"
#include "types.h"
int len;
char buffer[128];


typedef struct{
	int a;
	int b;
} ab;


ab x;

void main(){
	uart_init();

	while(1){
		len=0;
		while(len<10)
			len+=uart_read(0, buffer+len, 10-len);

		uart_write(0, buffer, 10);
	}

	ab *aa=(ab*)container_of(&x.b ,ab, b);
	aa=aa;
}


