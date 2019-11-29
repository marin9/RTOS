#include "cpu.h"
#include "rpi.h"
#include "task.h"
#include "time.h"
#include "types.h"
#include "mpool.h"
#include "timers.h"
#include "string.h"
#include "device.h"
#include "interrupt.h"


void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();
void test14();

void blink();


void main(){
	uart_init();
	pic_init();
	interrupt_init();
	timer_init();
	task_init();
	time_init();
	timers_init();

	task_create(blink, 0, 0, 1024, "main");
	task_start();
}
