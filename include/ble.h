#ifndef BLE_H
#define BLE_H
#include "arduino.h"

class BLE{
private:
    const char* _name;
public:
    void config();
    void init();
    void addNode(int id, const char* name, const char* svrUUID, const char* charUUID);
    void deleteNode(uint64_t id);
    void sendMsg(int id, const char* );
    void loop();
};

#endif
