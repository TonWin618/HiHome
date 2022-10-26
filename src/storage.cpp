#include "storage.h"

Preferences pref;

void prefInit(){
    pref.begin("gateway");
}

void keyPut(){

}

void keyGet(){

}

void initPut(){

}

void initGet(){
    
}

void wifiPut(String ssid, String password){
    pref.putString(WIFI_SSID, ssid);
    pref.putString(WIFI_PASSWORD, password);
}

void wifiGet(Network* client){
    client->config(
        pref.getString(WIFI_SSID),
        pref.getString(WIFI_PASSWORD)
    );
}

void mqttPut(const char * broker, const char* clientid, const char * username, const char * password, const int port){
    pref.putString(MQTT_BROKER, broker);
    pref.putInt(MQTT_PORT, port);
    pref.putString(MQTT_CLIENTID, clientid);
    pref.putString(MQTT_USERNAME, username);
    pref.putString(MQTT_PASSWORD, password);
}

void mqttGet(MqttClient* client){
    client->config(pref.getString(MQTT_BROKER).c_str(), 
        pref.getString(MQTT_CLIENTID).c_str(),
        pref.getString(MQTT_USERNAME).c_str(), 
        pref.getString(MQTT_PASSWORD).c_str(), 
        pref.getInt(MQTT_PORT)
    );
}

void blePut(){

}

void bleGet(){

}

void bleNodePut(){

}

void bleNodeGet(Node* node ,int index){
    node->id = pref.getInt()
}



