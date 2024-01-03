#include <WiFi.h>
#include <mqttClient.h>
#include <network.h>
#include <ble.h>
#include <BluetoothSerial.h>
#include <storage.h>

BLE ble;
Network net;
MqttClient mqtt;
BluetoothSerial bt;

String gatewayId = "0";
String userId = "0";
bool isInitialized = false;


String prompt(String msg)
{
    bt.println(msg);
    while(bt.available() == false);
    return bt.readString();
}

void config()
{
    gatewayId = "0";
    bt.begin("Hi-Gateway", false);
    while (bt.hasClient() == 0);
    Serial.println("client connected to bluetooth");

    String wifiName;
    String wifiPassword;
    do{
        wifiName = prompt("Please input WiFi name: ");
        wifiPassword = prompt("Please input WiFi password: ");
        bt.println("connecting...");
        net.config(wifiName, wifiPassword);
    } while (net.init()==false);
    netPut(wifiName, wifiPassword);
    bt.println("Successfully connected to wifi. ");
    
    String userId;
    String authCode;
    do{
        userId = prompt("input user id: ");
        authCode = prompt("input verification code: ");
        bt.println("connecting...");
        mqtt.config("tonwin.work", userId, "tryconnect", authCode, 1883);
        mqtt.setNetwork(net.client);
    } while (mqtt.init()==false);
    bt.println("Successfully connected to mqtt broker. ");
    mqtt.client.subscribe(userId.c_str());
    while(gatewayId == "0"){
        mqtt.client.loop();
    }
    idPut(gatewayId);
    uidPut(userId);
    mqttPut("tonwin.work", "device" + gatewayId, "device", authCode, 1883);
    bt.println("config successfully! ");

    isInitialized = true;
    initPut(isInitialized);
}

void setup()
{
    Serial.begin(115200);
    initGet(&isInitialized);
    if (!isInitialized)
    {
        Serial.println("start config");
        config();
    }else{
        idGet(&gatewayId);
        uidGet(&userId);
        netGet(&net);
        mqttGet(&mqtt);

        net.init();
        ble.addNode("3", "0000ffe0-0000-1000-8000-00805f9b34fb", "0000ffe1-0000-1000-8000-00805f9b34fb");
        ble.addNode("11", "e7810a71-73ae-499d-8c15-faa9aef0c3f2", "bef8d6c9-9c21-4c9e-b632-bd58c1009f9f");
        ble.init();
        mqtt.setNetwork(net.client);
        mqtt.init();
        mqtt.broadcast(gatewayId, "online");
    }
}

void loop()
{
    mqtt.client.loop();
    ble.loop();
}
