#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ble.h>

class MqttClient{
private:
    const char *_broker;
    const char * _topic = "3";
    const char *_clientid;
    const char *_username;
    const char *_password;
    int _port = 1883;
public:
    PubSubClient client;
    void config(const char * broker, const char* clientid, const char * username, const char * password, const int port, Client& WiFiClient);
    void init();
    void broadcast(int id, const char* data);
};

#endif