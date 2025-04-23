#include "pico/stdlib.h"
#include <stdio.h>
#include "functions.h"

//motion sensor
float measureDistance() {
    gpio_put(TRIGGER_PIN, 0);
    sleep_us(2);
    gpio_put(TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN, 0);

    uint64_t startTime = 0, endTime = 0;
    while (gpio_get(ECHO_PIN) == 0) {
        startTime = time_us_64();
    }
    while (gpio_get(ECHO_PIN) == 1) {
        endTime = time_us_64();
    }

    uint64_t duration = endTime - startTime;
    float distance = (duration * 0.0343) / 2;
    return distance;
}

//alarm part, might expand when i buy alarm
void buzz(int buzz_dur) {
	for (int i = 0; i < buzz_dur / 100; i++) {  
		gpio_put(BUZZER_PIN, 1);        
		sleep_ms(100);              
		gpio_put(BUZZER_PIN, 0);        
		sleep_ms(100);              
	}
}

