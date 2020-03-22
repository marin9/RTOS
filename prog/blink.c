#include "api.h"
#include "device.h"

#define LED_PIN		47


void tt(){
	int x;
	soft_pwm_init();
	soft_pwm_open(0, 21);

	while(1){
		for(x=0;x<20;++x){
			soft_pwm_write(0, x);
			os_task_sleep(500);
		}
	}
}


void blink(){
	tt();
	gpio_open(LED_PIN, GP_OUT);

	while(1){
		os_task_sleep(500);
		gpio_write(LED_PIN, GP_HIGH);
		os_task_sleep(500);
		gpio_write(LED_PIN, GP_LOW);
	}
}
