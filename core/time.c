#include "rpi.h"
#include "task.h"
#include "time.h"
#include "param.h"
#include "types.h"
#include "device.h"
#include "interrupt.h"


static uint ticks;


void time_tick(){
	++ticks;
	timer_set(TICK_TIME);
	task_yield();
}


void time_init(){
	pic_enable(SYSTMR1_IRQ);
	interrupt_register(SYSTMR1_IRQ, time_tick);
	timer_set(TICK_TIME);
	ticks=0;
}

uint time_get_ticks(){
	return ticks;
}

void time_delay(uint us){
	uint tv=timer_get()+us;
	while(tv>timer_get());
}
