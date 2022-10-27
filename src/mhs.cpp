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
    Serial.println("responseMqttAdd");
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,data);
    int _id = doc["id"];
    std::string id = std::to_string(_id);
    Serial.println(_id);
    Serial.println(id.c_str());
    gatewayId = id;
    response("mqtt_add","true");
    Serial.println("responseMqttAdd");
    return true;
}

void distribute(String msg){
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc,msg);
    if(!error){
        uint64_t _id = doc["id"];
        String id = String(_id);
        String data = doc["data"];
        if(id == gatewayId){
            String resType = doc["data"]["request"];
            if(resType == "ble_tryconnect"){
                responseBleTryConnect(data);
            }else if(resType == "ble_add"){
                responseBleAdd(data);
            }else if(resType == "mqtt_add"){
                responseMqttAdd(data);
            }
        }else{
            ble.sendMsg(id,data);
        }
    }
}



