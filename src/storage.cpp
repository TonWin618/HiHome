#include "storage.h"

Preferences pref;

void prefInit(){
    pref.begin("gateway");
}

void keyPut(){

}

void keyGet(){

}

void initPut(bool isInit){
    pref.putBool(IS_INITIALIZED, isInit);
}

void initGet(bool* isInit){
    *isInit = pref.getBool(IS_INITIALIZED);
}

void idPut(String id){
    pref.putString(GATEWAY_ID, id);
}

void idGet(String* id){
    *id = pref.getString(GATEWAY_ID);
}

void uidPut(String uid){
    pref.putString(USER_ID, uid);
}

void uidGet(String* uid){
    pref.getString(USER_ID);
}

void netPut(String ssid, String password){
    pref.putString(WIFI_SSID, ssid);
    pref.putString(WIFI_PASSWORD, password);
}

void netGet(Network* client){
    client->config(
        pref.getString(WIFI_SSID),
        pref.getString(WIFI_PASSWORD)
    );
}

void mqttPut(String broker, String clientid, String username, String password, uint16_t port){
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
        pref.getUInt(MQTT_PORT)
    );
}

void bleNodePut(Node* node, int index, String* id, String* svruuid, String* charuuid){
    pref.putString(BLENODE_ID + index, *id);
    pref.putString(BLENODE_SVRUUID + index, *svruuid);
    pref.putString(BLENODE_CHARUUID + index, *charuuid);
}

void bleNodeGet(Node* node,int index){
    node->id = pref.getInt(BLENODE_ID + index);
    node->svrUUID = pref.getString(BLENODE_SVRUUID + index);
    node->charUUID = pref.getString(BLENODE_CHARUUID + index);
}

void bleNodesGet(Node** pNodes,int total){
    Node* pNode = *pNodes;
    for(int i=0; i<total; i++){
        bleNodeGet(pNode, i);
        pNode++;
    }
}

void bleGet(String* name, int* count){
    *name = pref.getString(BLE_NAME);
    *count = pref.getUInt(BLE_NODECOUNT);
}



