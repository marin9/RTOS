#include "api.h"
#include "device.h"

#define SPWM_COUNT	8
#define SPWM_RES	20


static uint spwm_pin[SPWM_COUNT];
static uint spwm_val[SPWM_COUNT];
static uint spwm_cnt[SPWM_COUNT];


static void soft_pwm_task(){
	int i;

	while(1){
		for(i=0;i<SPWM_COUNT;++i){
			if(!spwm_pin[i])
				continue;

			if(spwm_cnt[i] >= spwm_val[i]){
				gpio_write(spwm_pin[i], GP_LOW);
			}else{
				gpio_write(spwm_pin[i], GP_HIGH);
			}

			++spwm_cnt[i];
			if(spwm_cnt[i] >= SPWM_RES){
				spwm_cnt[i]=0;
			}
		}
		os_task_sleep(1);
	}
}


void soft_pwm_init(){
	int i;

	for(i=0;i<SPWM_COUNT;++i){
		spwm_pin[i]=0;
		spwm_val[i]=0;
		spwm_cnt[i]=0;
	}
	os_task_create(soft_pwm_task, 0, 0, STACK_DEFAULT, 0);
}

void soft_pwm_open(uint n, uint pin){
	spwm_pin[n]=pin;
	spwm_val[n]=0;
	spwm_cnt[n]=0;
	gpio_open(pin, GP_OUT);
}

void soft_pwm_write(uint n, uint val){
	if(val >= SPWM_RES)
		val=SPWM_RES-1;

	spwm_val[n]=val;
	spwm_cnt[n]=0;
}
