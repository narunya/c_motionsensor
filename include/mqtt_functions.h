#pragma once
#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

void mqtt_connection_cb(mqtt_client_t *client, void *arg,mqtt_connection_status_t status);
int mqtt_connect(mqtt_client_t **client, const char *server_id, const char*client_id,struct mqtt_connect_client_info_t *info);
void mqtt_pub_motion_read(mqtt_client_t *client, const char *topic,const char* message);
extern volatile bool mqtt_connected;

#endif
