#ifndef BLE_H
#define BLE_H
#include "arduino.h"
#include "BLEDevice.h"
#include "mqttClient.h"

struct Node{
    int  id;
    char     svrUUID[40];
    char     charUUID[40];
    bool      state;
    BLEClient* pclient;
    BLERemoteCharacteristic* pCharacteristics;
    BLEAdvertisedDevice* pDevice;
};

class BLE{
private:
    const char* _name;
public:
    void config();
    void init();
    void addNode(int id, const char* svrUUID, const char* charUUID);
    void deleteNode(uint64_t id);
    void sendMsg(int id, const char* );
    void loop();
    bool tryConnect();
};

#endif
