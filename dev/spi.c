#include "rpi.h"
#include "device.h"

#define SPI_CS		((volatile uint*)(SPI_BASE+0x00))
#define SPI_FIFO	((volatile uint*)(SPI_BASE+0x04))
#define SPI_CLK		((volatile uint*)(SPI_BASE+0x08))
#define SPI_DLEN	((volatile uint*)(SPI_BASE+0x0C))
#define SPI_LTOH	((volatile uint*)(SPI_BASE+0x10))
#define SPI_DC		((volatile uint*)(SPI_BASE+0x14))


void spi_init(){
	gpio_open(7, GP_FN0);
	gpio_open(8, GP_FN0);
	gpio_open(9, GP_FN0);
	gpio_open(10, GP_FN0);
	gpio_open(11, GP_FN0);
}

void spi_readwrite(char *buf, uint n){
	uint i;

	*SPI_CS=0xB0;

	for(i=0;i<n;++i){
		while(!(*SPI_CS & (1<<18)));
		*SPI_FIFO=buf[i];
		
		while(!(*SPI_CS & (1<<16)));

		while(*SPI_CS & (1<<17))
			buf[i]=*SPI_FIFO;
	}
	*SPI_CS=0;
}
