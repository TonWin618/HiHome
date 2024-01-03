#include "ble.h"

#define MAX_CONNECT_NUM 5

extern MqttClient mqtt;

Node nodes[MAX_CONNECT_NUM];
static BLEScan* pBLEScan;
static BLEUUID curSvrUUID;
static BLEUUID curCharUUID;
uint8_t nodeIndex = 0;
uint8_t nodeCount = 0;
uint8_t connectedCount = 0;
bool doConnect = false;

/**
 * @brief 通知回调函数
 * 
 * @param pBLERemoteCharacteristic 消息来源特征
 * @param pData 传来的消息数据
 * @param length 消息长度
 * @param isNotify 是否通知
 */
static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    String id;
    for(int i = 0; i < nodeCount;i++){
      if(nodes[i].pCharacteristics->getUUID().toString() == pBLERemoteCharacteristic->getUUID().toString()){
        id = nodes[i].id;
      }
    }
    pData[length-1] ='\0';
    Serial.printf("BLE id:%d uuid:%s rx:%s\n", id, pBLERemoteCharacteristic->getUUID().toString().c_str(), (char*)pData);
    mqtt.broadcast(id,(char*)pData);
}

/**
 * @brief 蓝牙事件回调函数
 * 
 */
class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient* pclient) {
  }

  void onDisconnect(BLEClient* pclient) {
    connectedCount--;
    Serial.println("onDisconnect");
  }
};

/**
 * @brief 连接到一个BLE服务器节点
 * 
 * @return true 连接成功
 * @return false 连接失败
 */
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

/**
 * @brief 蓝牙扫描回调函数
 * 
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID()){
      BLEUUID uuid;
      for(int j =0; j < nodeCount; j++){
        uuid = BLEUUID(nodes[j].svrUUID.c_str());
        if(advertisedDevice.isAdvertisingService(uuid)){
          BLEDevice::getScan()->stop();
          nodeIndex = j;
          curSvrUUID = uuid;
          curCharUUID = BLEUUID(nodes[nodeIndex].charUUID.c_str());
          nodes[nodeIndex].pDevice = new BLEAdvertisedDevice(advertisedDevice);
          doConnect = true;
        }
      }
    }
  }
};

/**
 * @brief 初始化低功耗蓝牙模块
 * 
 */
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

void BLE::sendMsg(String id, String data){
  for(int i = 0; i<nodeCount; i++){
    if(nodes[i].id == id){
      Serial.print(data);
      nodes[i].pCharacteristics->writeValue((uint8_t*)data.c_str(), data.length());
      Serial.printf("BLE id:%d tx:%s lenth:%d\n",id, data, data.length());
    }
  }
}

/**
 * @brief 添加一个节点
 * 
 * @param id 设备id
 * @param name 设备名称，默认为蓝牙名称
 * @param svrUUID 服务UUID
 * @param charUUID 特征UUID
 */
void BLE::addNode(String id, String svrUUID, String charUUID){
  nodes[nodeCount].id = id;
  nodes[nodeCount].svrUUID = svrUUID;
  nodes[nodeCount].charUUID = charUUID;
  nodes[nodeCount].state = false;
  nodeCount++;
  Serial.println("add a new node");
}

/**
 * @brief 蓝牙循环检测是否有设备
 * 
 */
void BLE::loop(){
  if(doConnect){
    connectToServer();
  }
}

bool BLE::tryConnect(){
  return true;
}