#pragma once
#include "types.h"

#define GP_LOW 			0
#define GP_HIGH 		1
#define GP_IN			0
#define GP_OUT			1
#define GP_FN0			4
#define GP_FN1			5
#define GP_FN2			6
#define GP_FN3			7
#define GP_FN4			3
#define GP_FN5			2
#define GP_PULLOFF		(0<<4)
#define GP_PULLDOWN		(1<<4)
#define GP_PULLUP		(2<<4)
#define GP_NO_EDGE      0
#define GP_RISING_EDGE	1
#define GP_FALLING_EDGE	2
#define GP_HIGH_EDGE	3
#define GP_LOW_EDGE		4

#define MBOX_CH_POWER			0
#define MBOX_CH_FRAMEBUFFER		1
#define MBOX_CH_VIRTUAL_UART	2
#define MBOX_CH_VCHIQ			3
#define MBOX_CH_LEDS			4
#define MBOX_CH_BUTTONS			5
#define MBOX_CH_TOUCHSCREEN		6
#define MBOX_CH_ARM_VC			8
#define MBOX_CH_VC_ARM			9


void timer_init();
void timer_clr();
uint timer_get();
void timer_set(uint us);
void timer_wait(uint us);
void timer3_clr();
void timer3_set(uint us);

void pic_init();
void pic_enable(uint irqn);
void pic_disable(uint irqn);
uint pic_ispending(uint irqn);

void gpio_open(uint pin, int mode);
void gpio_write(uint pin, int val);
uint gpio_read(uint pin);
void gpio_enint(uint pin, void (*h)(), int edge);

void uart_init();
void uart_putc(char c);
void uart_getc(char *c);
void uart_print(char *s);
int uart_read(int unit, void* buffer, int size);
int uart_write(int unit, void* buffer, int size);

void i2c_init();
int i2c_read(uint id, char *buff, uint len);
int i2c_write(uint id, char *buff, uint len);

void pwm_init();
int pwm_write(int unit, void* buffer, int size);

void soft_pwm_init();
void soft_pwm_open(uint n, uint pin);
void soft_pwm_write(uint n, uint val);

void spi_init();
void spi_readwrite(char *buf, uint n);

void soft_spi_init(uint cs, uint ck, uint si, uint so);
void soft_spi_begin();
void soft_spi_end();
void soft_spi_sendByte(char byte);
char soft_spi_readByte();

void rand_init();
int rand_get(int min, int max);

void flash_init();
int flash_read(int unit, void* buffer, int nblocks, int offset);
int flash_write(int unit, void* buffer, int nblocks, int offset);

int mbox_call(int ch);

int mbox_framebuffer_init(uint *buff, uint w, uint h, uint p);
