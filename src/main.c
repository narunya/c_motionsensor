#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include "wifi_config.h"
#include "hardware/i2c.h"
#include "lcd.h"
#include "functions.h"

 
#include <lwip/ip_addr.h>
#include "lwip/apps/mqtt.h"

#include "mqtt_functions.h"
#include "mqtt_config.h"

void wifi();

int main(void) {
    stdio_init_all();
    sleep_ms(1000); // Give USB time to init

    // Init hardware
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Init I2C LCD
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SCL_PIN);
    lcd_init();

    // Connect to Wi-Fi
    wifi();
    sleep_ms(1000);

    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_print("Trying MQTT");

    // MQTT setup
    mqtt_client_t *client = NULL;
    struct mqtt_connect_client_info_t pico;
    if (!mqtt_connect(&client, _MQTT_BROKER_IP, MQTT_DEVICE_NAME, &pico)) {
        printf("MQTT connect failed\n");
    }

    // Wait until MQTT is connected (timeout after 10 seconds)
    int waited = 0;
    while (!mqtt_connected && waited < 10000) {
        cyw43_arch_poll();
        sleep_ms(10);
        waited += 10;
    }

    if (!mqtt_connected) {
        lcd_set_cursor(1, 0);
        lcd_print("MQTT failed!");
        while (1); // Stop here or retry logic
    }

    lcd_clear();
    lcd_print("MQTT connected");

    // Main loop
    while (1) {
        cyw43_arch_poll();

        float distance = measureDistance();
        bool alarm_react = (distance > ALARM_MIN && distance < ALARM_MAX);
        bool alarm_triggered = (distance < ALARM_TRIG);

        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%.2f cm", distance);
        lcd_search(buffer);

        if (alarm_react) {
            lcd_warning(buffer);
            buzz(200);  // Keep short
        }

        if (alarm_triggered) {
            lcd_alarm(buffer);
            buzz(1000);

            if (mqtt_connected) {
                const char *topic = "motion/sensor";
                const char *msg = "motion_detected";
                err_t pub_result = mqtt_publish(client, topic, msg, strlen(msg), 0, 0, NULL, NULL);

                if (pub_result == ERR_OK) {
                    printf("MQTT publish OK\n"); 
                } else {
                    printf("MQTT publish failed: %d\n", pub_result);
                }
            }
        }

        sleep_ms(100); 
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
        sleep_ms(1000);
	}
}
