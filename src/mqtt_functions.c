#include "lwip/apps/mqtt.h"
#include "pico/stdlib.h"
#include <lwip/ip_addr.h>
#include <lwip/netif.h>
#include <stdio.h>
#include <string.h>
#include "mqtt_config.h"
#include "mqtt_functions.h"

volatile bool mqtt_connected = false;

void mqtt_connection_cb(mqtt_client_t *client, void *arg,mqtt_connection_status_t status){
    if(status == MQTT_CONNECT_ACCEPTED) {
        printf("MQTT connect successfull! %d\n",status);
        mqtt_connected = true;
    }
    else {
        printf("MQTT connection failed %d\n",status);
        mqtt_connected = false;
    }
};

int mqtt_connect(mqtt_client_t **client, const char *server_id ,const char *client_id, struct mqtt_connect_client_info_t *info){

    info->client_id = client_id;
    info->client_user = NULL;
    info->client_pass = NULL;
    info->keep_alive = 60;
    info->will_topic = "pico/status";
    info->will_msg = "Connection lost";
    info->will_qos = 1;
    info->will_retain = 1;

    *client = mqtt_client_new();
    if(!(*client)) {
        printf("Failed to create MQTT_client \n");
        return 0;
    }

    ip_addr_t broker_ip;
    if(!ip4addr_aton(server_id,&broker_ip)) {
        printf("Invalid IP address format: %s\n", server_id);
        return 0;
    }
    mqtt_client_connect(*client, &broker_ip, _MQTT_PORT,mqtt_connection_cb, NULL, info);
    return 1;
};

void mqtt_pub_motion_read(mqtt_client_t *client,const char *topic,const char *message){
    err_t pub_err = mqtt_publish(client,topic,message,strlen(message),1,0,NULL,NULL);
    if(pub_err == ERR_OK) {
        printf("Message published to topic '%s'\n",topic);
    }
    else{
        printf("Failed to publish message: %d\n", pub_err);
    }
};
