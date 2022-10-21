#include <WiFi.h>
#include <mqttClient.h>
#include <network.h>
#include <ble.h>
#include <BluetoothSerial.h>

BLE ble;
Network net;
MqttClient mqtt;
BluetoothSerial bt;

int device_id;
int user_id;
bool doConfig = true;
bool btConnected = false;

String prompt(String msg)
{
    bt.println(msg);
    while(bt.available() == false);
    return bt.readString();
}

void config()
{
    bt.begin("Hi-Gateway", false);
    while (bt.hasClient() == 0);
    Serial.println("client connected to bluetooth");

    String wifiName;
    String wifiPassword;
    do{
        wifiName = prompt("Please input WiFi name: ");
        wifiPassword = prompt("Please input WiFi password: ");
        bt.println("connecting...");
        net.set(wifiName, wifiPassword);
    } while (net.init()==false);
    bt.println("Successfully connected to wifi. ");

    String userId;
    String deviceId;
    String authCode;
    do{
        userId = prompt("input user id: ");
        deviceId = prompt("input device id: ");
        authCode = prompt("input verification code: ");
        char clientId[30] = "device";
        bt.println("connecting...");
        mqtt.config("110.42.139.225",strcat(clientId,deviceId.c_str()),"gateway",authCode.c_str(),1883,net.client);
    }while (mqtt.init()==false);
    mqtt.client.subscribe(userId.c_str());
    mqtt.broadcast(deviceId.toInt(),"{status:online}");
    bt.println("Successfully connected to mqtt broker. ");
    bt.println("config successfully! ");
}

void setup()
{
    Serial.begin(115200);
    if (doConfig)
    {
        Serial.println("start config");
        config();
    }else{
        net.set("QQQ", "19818308676");
        net.init();
        ble.addNode(3, "Hi-Light", "0000ffe0-0000-1000-8000-00805f9b34fb", "0000ffe1-0000-1000-8000-00805f9b34fb");
        ble.addNode(11, "JDY34", "e7810a71-73ae-499d-8c15-faa9aef0c3f2", "bef8d6c9-9c21-4c9e-b632-bd58c1009f9f");
        ble.init();
        mqtt.config("110.42.139.225", "device6", "device", "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MywiaWF0IjoxNjY1NTc0NTYwfQ.2MMIiJG4gO95CBAYWjeg-nU4uxv17HfH3t9EO2ikkVU", 1883, net.client);
        mqtt.init();
        mqtt.broadcast(device_id, "online");
    }
    
}

void loop()
{
    mqtt.client.loop();
    ble.loop();
}
