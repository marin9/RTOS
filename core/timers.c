#include "rpi.h"
#include "types.h"
#include "param.h"
#include "device.h"
#include "interrupt.h"


typedef struct{
	uint run;
	uint counter;
	uint period;
	void (*handler)();
} timer_t;

static timer_t timers[TIMERS_COUNT];


static void timers_handler(){
	int i;
	timer3_set(1000);

	for(i=0;i<TIMERS_COUNT;++i){
		if(timers[i].run==1){
			--timers[i].counter;

			if(!timers[i].counter){
				timers[i].handler();
				timers[i].counter=timers[i].period;
				if(!timers[i].period){
					timers[i].run=0;
				}
			}
		}
	}
}


void timers_init(){
	int i;
	for(i=0;i<TIMERS_COUNT;++i){
		timers[i].run=0;
	}
	pic_enable(SYSTMR3_IRQ);
	interrupt_register(SYSTMR3_IRQ, timers_handler);
	timer3_set(1000);
}


void tmr_init(uint id, uint start, uint period, void (*handler)()){
	if(id>=TIMERS_COUNT){
		return;
	}

	timers[id].run=0;
	timers[id].counter=start;
	timers[id].period=period;
	timers[id].handler=handler;

	if(!start){
		timers[id].counter=period;
	}
}

void tmr_start(uint id){
	if(id>=TIMERS_COUNT){
		return;
	}
	timers[id].run=1;
}

void tmr_stop(uint id){
	if(id>=TIMERS_COUNT){
		return;
	}
	timers[id].run=0;
}

uint tmr_value(uint id){
	if(id>=TIMERS_COUNT){
		return 0;
	}
	return timers[id].counter;
}
