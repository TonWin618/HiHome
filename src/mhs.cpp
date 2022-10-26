#include "mhs.h"

extern MqttClient mqtt;
extern BLE ble;
extern String gatewayId;

bool response(String resType, String resVal){
    StaticJsonDocument<200> doc;
    char msg[200];
    doc["response"] = resType;
    doc["return"] = resVal;
    serializeJson(doc,msg,200);
    mqtt.broadcast(gatewayId,msg);
    return true;
}

bool responseBleTryConnect(String data){
    if(ble.tryConnect()){
        response("ble_tryconnect","true");
    }
}

bool responseBleAdd(String data){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,data);
    String id = doc["id"];
    String svrUUID = doc["svr_uuid"];
    String charUUID = doc["char_uuid"];
    ble.addNode(id, svrUUID, charUUID);
    response("ble_add","true");
    return true;
}

bool responseMqttAdd(String data){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,data);
    int id = doc["id"];
    gatewayId = id;
    response("mqtt_add","true");
    return true;
}

void distribute(String msg){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,msg);
    if(!error){
        String id = doc["id"];
        String data = doc["data"];
        if(id == gatewayId){
            String resType = doc["data"]["response"];
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



