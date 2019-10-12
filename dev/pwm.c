#include "rpi.h"
#include "device.h"

#define PWM_CONTROL		((volatile uint*)(PWM_BASE+0x00))
#define PWM_STATUS		((volatile uint*)(PWM_BASE+0x04))
#define PWM0_RANGE		((volatile uint*)(PWM_BASE+0x10))
#define PWM0_DATA		((volatile uint*)(PWM_BASE+0x14))
#define PWM_FIFO    	((volatile uint*)(PWM_BASE+0x18))
#define PWM1_RANGE		((volatile uint*)(PWM_BASE+0x20))
#define PWM1_DATA		((volatile uint*)(PWM_BASE+0x24))
#define PWMCLK_CNTL		((volatile uint*)(CLOCK_BASE+0xA0))
#define PWMCLK_DIV		((volatile uint*)(CLOCK_BASE+0xA4))

#define PM_PASS 		0x5A000000 

#define PWM1_MS_MODE    0x8000  // Run in MS mode
#define PWM1_USEFIFO    0x2000  // Data from FIFO
#define PWM1_REVPOLAR   0x1000  // Reverse polarity
#define PWM1_OFFSTATE   0x0800  // Ouput Off state
#define PWM1_REPEATFF   0x0400  // Repeat last value if FIFO empty
#define PWM1_SERIAL     0x0200  // Run in serial mode
#define PWM1_ENABLE     0x0100  // Channel Enable
#define PWM0_MS_MODE    0x0080  // Run in MS mode
#define PWM0_USEFIFO    0x0020  // Data from FIFO
#define PWM0_REVPOLAR   0x0010  // Reverse polarity
#define PWM0_OFFSTATE   0x0008  // Ouput Off state
#define PWM0_REPEATFF   0x0004  // Repeat last value if FIFO empty
#define PWM0_SERIAL     0x0002  // Run in serial mode
#define PWM0_ENABLE     0x0001  // Channel Enable

#define BERR  			0x100
#define GAPO4 			0x80
#define GAPO3 			0x40
#define GAPO2 			0x20
#define GAPO1 			0x10
#define RERR1 			0x8
#define WERR1 			0x4
#define EMPT1 			0x2
#define FULL1 			0x1



void pwm_init(){
    uint div=40000;
    uint range=0x100;

    gpio_open(12, GP_FN0);

    *PWMCLK_CNTL=PM_PASS | (1<<5);
    *PWMCLK_DIV=PM_PASS | div;
    *PWMCLK_CNTL=PM_PASS | 16 | 1;
    timer_wait(2000);

    *PWM_CONTROL=0;    
    timer_wait(2000);

    *PWM0_RANGE=range;
    *PWM_CONTROL=PWM0_USEFIFO | PWM0_ENABLE | 1<<6;
    timer_wait(2000);
}


int pwm_write(int unit, void* buffer, int size){
    if(unit!=0)
        return -1;

	int i=0;
    char *b=(char*)buffer;

    while(size && !(*PWM_STATUS & FULL1)){
        *PWM_FIFO=(int)b[i];
        ++i;
        --size;
    }
    return i;
}
