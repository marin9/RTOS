#include "api.h"
#include "device.h"

#define LED_PIN		47



void blink(){
	gpio_open(LED_PIN, GP_OUT);

	while(1){
		os_task_sleep(500);
		gpio_write(LED_PIN, GP_HIGH);
		os_task_sleep(500);
		gpio_write(LED_PIN, GP_LOW);
	}
}
