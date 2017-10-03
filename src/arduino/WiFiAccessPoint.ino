#include <ESP8266WiFi.h>

bool setupAP(const char *ssid, const char *password)
{
    bool b = WiFi.softAP(ssid, password);

    if (b)
    {
        Serial.print("Started access point at ");
        Serial.println(WiFi.softAPIP());
    }
    else
    {
        Serial.println("Failed to start access point");
    }

    return b;
}