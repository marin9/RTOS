#include "types.h"

#define SYSTMR_BASE		0x20003000
#define SYS_TIMER_CS	((volatile uint*)(SYSTMR_BASE+0x00))
#define SYS_TIMER_CLO	((volatile uint*)(SYSTMR_BASE+0x04))
#define SYS_TIMER_CHI	((volatile uint*)(SYSTMR_BASE+0x08))
#define SYS_TIMER_C1	((volatile uint*)(SYSTMR_BASE+0x10))
#define SYS_TIMER_C3	((volatile uint*)(SYSTMR_BASE+0x18))


void timer_init(){
}

void timer_set(uint us){
	*SYS_TIMER_CS=1<<1;
	*SYS_TIMER_C1=*SYS_TIMER_CLO+us;
}

uint timer_get(){
	return *SYS_TIMER_CLO;
}
