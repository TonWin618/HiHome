#include <network.h>

int timeOut = 5000;//连接超时时间，单位ms

//设置wifi名称和密码
void Network::set(String ssid, String password){
	_ssid = ssid;
	_password = password;
}

//连接wifi
bool Network::init()
{
	int timeWait = 0;
    Serial.println("scan start");
	int n = WiFi.scanNetworks();
	Serial.println("scan done");
	if (n == 0)
	{
		Serial.println("no networks found");
		return false;
	}
	else
	{
		Serial.print(n);
		Serial.println(" networks found");
		for (int i = 0; i < n; ++i)
		{
			Serial.print(i + 1);
			Serial.print(": ");
			Serial.print(WiFi.SSID(i));
			Serial.print(" (");
			Serial.print(WiFi.RSSI(i));
			Serial.print(")");
			Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
			delay(10);
		}
	}
	Serial.println("");
	Serial.print("Connecting: ");
	Serial.print(_ssid.c_str());
	Serial.print(" @");
	Serial.println(_password.c_str());

	WiFi.begin(_ssid.c_str(), _password.c_str());
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		timeWait += 500;
		Serial.print(".");
		if(timeWait > timeOut){
			Serial.println("WiFi connection timeout");
			return false;
		}
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	return true;
}