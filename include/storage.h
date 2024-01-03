#include "Preferences.h"
#include "network.h"
#include "mqttClient.h"
#include "ble.h"

#define GATEWAY_ID "gateway_id"
#define USER_ID "user_id"
#define IS_INITIALIZED "is_initialize"
#define AUTHCODE "authcode"

#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "wifi_password"

#define BLE_NAME "ble_name"
#define BLE_NODECOUNT "ble_nodecount"
#define BLENODE_ID "blenode_id"
#define BLENODE_SVRUUID "blenode_srvuuid"
#define BLENODE_CHARUUID "blenode_charuuid"

#define MQTT_CLIENTID "mqtt_clientId"
#define MQTT_USERNAME "mqtt_username"
#define MQTT_PASSWORD "mqtt_password"
#define MQTT_BROKER "mqtt_broker"
#define MQTT_PORT "mqtt_port"

void initPut(bool isInit);
void initGet(bool* isInit);

void idPut(String id);
void idGet(String* id);
void uidPut(String uid);
void uidGet(String* uid);

void netPut(String ssid, String password);
void netGet(Network* client);
void mqttPut(String broker, String clientid, String username, String password, uint16_t port);
void mqttGet(MqttClient* client);