#ifndef FUNC_H
#define FUNC_H

#include "pico/stdlib.h"

#define BUZZER_PIN 14
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define SDA_PIN 4
#define SCL_PIN 5

#define ALARM_MIN 10
#define ALARM_MAX 15
#define ALARM_TRIG 9.99

void buzz(int buzz_dur);  
float measureDistance(void); 
 
#endif
