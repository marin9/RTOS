

void uart_init();
int uart_read(int unit, void* buffer, int size);
int uart_write(int unit, void* buffer, int size);


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


