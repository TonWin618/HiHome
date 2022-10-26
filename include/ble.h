#ifndef BLE_H
#define BLE_H
#include "arduino.h"
#include "BLEDevice.h"
#include "mqttClient.h"

struct Node{
    String id;
    String svrUUID;
    String charUUID;
    bool state;
    BLEClient* pclient;
    BLERemoteCharacteristic* pCharacteristics;
    BLEAdvertisedDevice* pDevice;
};

class BLE{
private:
    String _name;
public:
    void config();
    void init();
    void addNode(String id, String svrUUID, String charUUID);
    void deleteNode(String id);
    void sendMsg(String id, String );
    void loop();
    bool tryConnect();
};

#endif
