#include <mqttClient.h>
#include "mhs.h"

extern BLE ble;

void MqttClient::config(String broker,String clientid, String username, String password, uint16_t port){
    _broker = broker;
    _clientid = clientid;
    _username = username;
    _password = password;
    _port = port;
}

void MqttClient::setNetwork(Client& WiFiClient){
    client.setClient(WiFiClient);
}

//将蓝牙接口或本机的消息发送到用户主题
void MqttClient::broadcast(String id,String data){
    StaticJsonDocument<200> doc;
    char msg[200];
    doc["id"] = id;
    doc["data"] = data;
    serializeJson(doc,msg,200);
    client.publish(_topic.c_str(),msg);
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
    client.setServer(_broker.c_str(), _port);
    client.setCallback(callback);
    while (!client.connected()) {
        Serial.printf("The client connects to the public mqtt broker\n");
        if (client.connect(_clientid.c_str(), _username.c_str(), _password.c_str())) {
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

