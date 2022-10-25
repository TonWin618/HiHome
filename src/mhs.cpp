#include "mhs.h"

extern MqttClient mqtt;
extern BLE ble;
extern int gatewayId;

bool response(const char* resType, const char* resVal){
    StaticJsonDocument<200> doc;
    char msg[200];
    doc["response"] = resType;
    doc["return"] = resVal;
    serializeJson(doc,msg,200);
    mqtt.broadcast(gatewayId,msg);
    return true;
}

void distribute(const char* msg){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,msg);
    if(!error){
        int id = doc["id"];
        const char* data = doc["data"];
        if(id == gatewayId){
            const char* resType = doc["data"]["response"];
            if(resType == "ble_tryconnect"){
                responseBleTryConnect(data);
            }else if(resType == "ble_add"){
                responseBleAdd(data);
            }
        }else{
            ble.sendMsg(id,data);
        }
    }
}



bool responseBleTryConnect(const char* data){
    if(ble.tryConnect()){
        response("ble_tryconnect","true");
    }
}

bool responseBleAdd(const char* data){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,data);
    int id = doc["id"];
    const char* svrUUID = doc["svr_uuid"];
    const char* charUUID = doc["char_uuid"];
    ble.addNode(id, svrUUID, charUUID);
    response("ble_add","true");
    return true;
}

bool responseMqttAdd(const char* data){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,data);
    int id = doc["id"];
    gatewayId = id;
    response("mqtt_add","true");
    return true;
}