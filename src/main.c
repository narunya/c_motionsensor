#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include "wifi_config.h"
#include "hardware/i2c.h"
#include "lcd.h"
#include "functions.h"

void wifi();

int main() {
	sleep_ms(1000);
    stdio_init_all();
    
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    
    // Initialize I2C0 at 100kHz on default SDA and SCL pins for the Pico
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SCL_PIN);
    lcd_init();

    wifi(); // Connect to Wi-Fi


  
    while (true) {
    	float distance = measureDistance();
    	bool alarm_react = (distance > ALARM_MIN && distance < ALARM_MAX);
    	bool alarm_triggered = (distance < ALARM_TRIG);
    	char buffer[16];
    	snprintf(buffer, sizeof(buffer), "%.2f cm", distance); //float converter
		lcd_search(buffer); // motion sensor printer
		
		if (alarm_react){
			lcd_warning(buffer);
			buzz(200);
		}
		
        if (alarm_triggered){
        	lcd_alarm(buffer);
        	buzz(2000);
        	sleep_ms(500); // Delay to avoid multiple triggers
        }
        sleep_ms(250); // Small delay between measurements
	}

    return 0;
}

void wifi() {
    cyw43_arch_init(); 
    cyw43_arch_enable_sta_mode();

    lcd_clear();
    lcd_set_cursor(0, 0); 
    lcd_print("Connecting to");
    lcd_set_cursor(1, 0);
    lcd_print(WIFI_SSID);
    
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        lcd_print("Failed!");
    } else {
    	lcd_clear();
    	lcd_set_cursor(0, 0); 
        lcd_print("Connected!");
        sleep_ms(2000);
    }
}
