#include <WiFi.h>
#include <mqttClient.h>
#include <network.h>
#include <ble.h>

BLE ble;
Network net;
MqttClient mqtt;

int device_id;
int user_id;

void setup() {
    Serial.begin(115200);
    net.set("QQQ","19818308676");
    net.init();
    ble.addNode(3,"Hi-Light","0000ffe0-0000-1000-8000-00805f9b34fb","0000ffe1-0000-1000-8000-00805f9b34fb");
    ble.addNode(11,"JDY34","e7810a71-73ae-499d-8c15-faa9aef0c3f2","bef8d6c9-9c21-4c9e-b632-bd58c1009f9f");
    ble.init();
    mqtt.config("tonwin.work","device6","device","eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MywiaWF0IjoxNjY1NTc0NTYwfQ.2MMIiJG4gO95CBAYWjeg-nU4uxv17HfH3t9EO2ikkVU", 1883, net.client);
    mqtt.init();
    //mqtt.broadcast(6, "online");

}

void loop() {
    mqtt.client.loop();
    ble.loop();
}