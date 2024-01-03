#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <ble.h>

class MqttClient{
private:
    String _broker;
    String  _topic;
    String _clientid;
    String _username;
    String _password;
    uint16_t _port;
public:
    PubSubClient client;
    void config(String broker,String clientid, String username, String password, uint16_t port);
    void setNetwork(Client& WiFiClient);
    bool init();
    void broadcast(String id, String data);
};

#endif