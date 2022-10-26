#include <mqttClient.h>
#include "mhs.h"

extern BLE ble;

void MqttClient::config(const char * broker, const char* clientid, const char * username, const char * password, const int port){
    _broker = broker;
    _clientid = clientid;
    _username = username;
    _password = password;
    _port = port;
}

void MqttClient::config(const char * broker, const char* clientid, const char * username, const char * password, const int port, Client& WiFiClient){
    config(broker,clientid,username,password,port);
    client.setClient(WiFiClient);
}

//将消息中data分发到消息中id所对应的设备

//将蓝牙接口或本机的消息发送到用户主题
void MqttClient::broadcast(int id,const char* data){
    StaticJsonDocument<200> doc;
    char msg[200];
    doc["id"] = id;
    doc["data"] = data;
    serializeJson(doc,msg,200);
    client.publish(_topic,msg);
}

//接收到mqtt消息时触发
void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    distribute((char*)payload);
}

//mqtt初始化
bool MqttClient::init(){
    client.setServer(_broker, _port);
    client.setCallback(callback);
    while (!client.connected()) {
        Serial.printf("The client connects to the public mqtt broker\n");
        if (client.connect(_clientid, _username, _password)) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
            return false;
        }
    }
    return true;
}

