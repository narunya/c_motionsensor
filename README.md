# current Motionsensor + lcd (C/C++)

current pico W wifi, lcd, motionsensor, buzzer

## Dependancies

* Raspberry Pi Pico SDK
* CMake
* Make

## Installation

1.  **Clone:**
```bash
    git clone https://github.com/narunya/c_motionsensor.git
```

2.  **Create headerfile with WiFi-credentials:**
```bash
    cat > include/wifi_config.h << EOF
    #ifndef WIFI_CONFIG_H
    #define WIFI_CONFIG_H
    
    #define WIFI_SSID "YOUR_WIFI_ID"
    #define WIFI_PASS "YOUR_WIFI_PW"
    
    #endif 
EOF
```

2.1 **Create headerfile with MQTT-configuration:**
```bash
#pragma once

#define _MQTT_BROKER_IP "YOUR_BROKER_IP"
#define _MQTT_PORT 1883 // standard port

#ifndef MQTT_DEVICE_NAME
#define MQTT_DEVICE_NAME "pico-w" // change name on your device if you want..

#endif

```


3. **You can find and change LCD, BUZZER and MOTIONSENSOR pins in /include/functions.h**
```
//pins
#define BUZZER_PIN 14
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define SDA_PIN 4
#define SCL_PIN 5

//alarm threshold in cm
#define ALARM_MIN 10
#define ALARM_MAX 15
#define ALARM_TRIG 9.99
```

4.  **build project:**
```bash
    mkdir build
    cd build
    cmake ..
    make 
```

5.  **move .uf2 file :**

build/bin -> pico-w
