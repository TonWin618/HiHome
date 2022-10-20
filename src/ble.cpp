#include "ble.h"
#include "BLEDevice.h"
#include "mqttClient.h"

#define MAX_CONNECT_NUM 5

extern MqttClient mqtt;

struct Node{
    int  id;
    char     name[30];
    char     svrUUID[40];
    char     charUUID[40];
    bool      state;
    BLEClient* pclient;
    BLERemoteCharacteristic* pCharacteristics;
    BLEAdvertisedDevice* pDevice;
};
Node nodes[MAX_CONNECT_NUM];

static BLEScan* pBLEScan;
static BLEUUID curSvrUUID;
static BLEUUID curCharUUID;

uint8_t nodeIndex = 0;
uint8_t nodeCount = 0;
uint8_t connectedCount = 0;
bool doConnect = false;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    int id;
    for(int i = 0; i < nodeCount;i++){
      if(nodes[i].pCharacteristics->getUUID().toString() == pBLERemoteCharacteristic->getUUID().toString()){
        id = nodes[i].id;
      }
    }
    pData[length-1] ='\0';
    Serial.printf("BLE id:%d uuid:%s rx:%s\n", id, pBLERemoteCharacteristic->getUUID().toString().c_str(), (char*)pData);
    mqtt.broadcast(id,(char*)pData);
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connectedCount--;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
    doConnect = false;
    Serial.print("Forming a connection to ");
    Serial.println(nodes[nodeIndex].pDevice->getAddress().toString().c_str());

    nodes[nodeIndex].pclient  = BLEDevice::createClient();
    Serial.println(" - Created client");
    nodes[nodeIndex].pclient->setClientCallbacks(new MyClientCallback());
    
    nodes[nodeIndex].pclient->connect(nodes[nodeIndex].pDevice);
    Serial.println(" - Connected to server");

    BLERemoteService* pRemoteService = nodes[nodeIndex].pclient->getService(curSvrUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(curSvrUUID.toString().c_str());
      nodes[nodeIndex].pclient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");

    nodes[nodeIndex].pCharacteristics = pRemoteService->getCharacteristic(curCharUUID);
    if (nodes[nodeIndex].pCharacteristics == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(curCharUUID.toString().c_str());
      nodes[nodeIndex].pclient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    if(nodes[nodeIndex].pCharacteristics->canRead()) {
      std::string value = nodes[nodeIndex].pCharacteristics->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(nodes[nodeIndex].pCharacteristics->canNotify())
      nodes[nodeIndex].pCharacteristics->registerForNotify(notifyCallback);

    connectedCount++;
    if(connectedCount<nodeCount)
      pBLEScan->start(5,true);
    return true;
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID()){
      BLEUUID uuid;
      for(int j =0; j < nodeCount; j++){
        uuid = BLEUUID(nodes[j].svrUUID);
        if(advertisedDevice.isAdvertisingService(uuid)){
          BLEDevice::getScan()->stop();
          nodeIndex = j;
          curSvrUUID = uuid;
          curCharUUID = BLEUUID(nodes[nodeIndex].charUUID);
          nodes[nodeIndex].pDevice = new BLEAdvertisedDevice(advertisedDevice);
          doConnect = true;
        }
      }
    }
  }
};

void BLE::init(){
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("Hi-Gateway");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}

void BLE::sendMsg(int id, const char* data){
  for(int i = 0; i<nodeCount; i++){
    if(nodes[i].id == id){
      Serial.print(data);
      int count = strlen(data);
      nodes[i].pCharacteristics->writeValue((uint8_t*)data, count);
      Serial.printf("BLE id:%d tx:%s lenth:%d\n",id, data, count);
    }
  }
}

void BLE::addNode(int id, const char* name, const char* svrUUID, const char* charUUID){
  nodes[nodeCount].id = id;
  strcpy(nodes[nodeCount].name,name);
  strcpy(nodes[nodeCount].svrUUID,svrUUID);
  strcpy(nodes[nodeCount].charUUID,charUUID);
  nodes[nodeCount].state = false;
  nodeCount++;
  Serial.println("add a new node");
}

void BLE::loop(){
  if(doConnect){
    connectToServer();
  }
}