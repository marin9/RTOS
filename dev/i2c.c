#include "rpi.h"
#include "device.h"

#define BSC0_C		((volatile uint*)(I2C_BASE+0x00))
#define BSC0_S		((volatile uint*)(I2C_BASE+0x04))
#define BSC0_DLEN	((volatile uint*)(I2C_BASE+0x08))
#define BSC0_A		((volatile uint*)(I2C_BASE+0x0C))
#define BSC0_FIFO	((volatile uint*)(I2C_BASE+0x10))
#define BSC0_DIV	((volatile uint*)(I2C_BASE+0x14))

#define BSC_C_I2CEN (1 << 15)
#define BSC_C_INTR 	(1 << 10)
#define BSC_C_INTT 	(1 << 9)
#define BSC_C_INTD 	(1 << 8)
#define BSC_C_ST 	(1 << 7)
#define BSC_C_CLEAR (1 << 4)
#define BSC_C_READ 	(1)
#define START_READ 	(BSC_C_I2CEN|BSC_C_ST|BSC_C_CLEAR|BSC_C_READ)
#define START_WRITE (BSC_C_I2CEN|BSC_C_ST)

#define BSC_S_CLKT 	(1 << 9)
#define BSC_S_ERR 	(1 << 8)
#define BSC_S_RXF 	(1 << 7)
#define BSC_S_TXE 	(1 << 6)
#define BSC_S_RXD 	(1 << 5)
#define BSC_S_TXD 	(1 << 4)
#define BSC_S_RXR 	(1 << 3)
#define BSC_S_TXW 	(1 << 2)
#define BSC_S_DONE 	(1 << 1)
#define BSC_S_TA 	(1)
#define CLEAR_STATUS (BSC_S_CLKT|BSC_S_ERR|BSC_S_DONE)

#define GPFSEL0     ((volatile uint*)(GPIO_BASE+0x00))



static int wait_i2c_done() {
	int timeout=50;

	while((!(*BSC0_S & BSC_S_DONE)) && --timeout) {
		timer_wait(500);
	}

	if(!timeout)
		return -1;
	else
		return 0;
}


void i2c_init(){
	*GPFSEL0 &= ~0x3f;
	*GPFSEL0 |= 0x24;

	*BSC0_DIV=0x100;
}

int i2c_read(uint id, char *buff, uint len){
	int i;
	int n = len>16 ? 16 : len;

	*BSC0_A = id;
	*BSC0_DLEN = n;
	*BSC0_S = CLEAR_STATUS;	// Reset status bits (see #define)
	*BSC0_C = START_READ;	// Start Read after clearing FIFO (see #define)

	if(wait_i2c_done())
		return -1;

	for(i=0;i<n;++i){
		buff[i] = *BSC0_FIFO & 0x7f;
	}

	return n;
}

int i2c_write(uint id, char *buff, uint len){
	int i;
	int n = len>16 ? 16 : len;

	*BSC0_A = id;
	*BSC0_DLEN = n;
	*BSC0_C = BSC_C_I2CEN|BSC_C_CLEAR;

	for(i=0;i<16;++i){
		*BSC0_FIFO = buff[i];
	}
	*BSC0_S = CLEAR_STATUS;	// Reset status bits (see #define)
	*BSC0_C = START_WRITE;	// Start Write (see #define)

    if(wait_i2c_done())
		return -1;

	return n;
}
