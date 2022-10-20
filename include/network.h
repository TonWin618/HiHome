#ifndef NETWORK_H
#define NETWORK_H

#include <WiFi.h>
#include <Arduino.h>

class Network
{
private:
	String _ssid;
    String _password;
public:
    WiFiClient client;
	bool init();
    void set(String ssid, String password);
};

#endif