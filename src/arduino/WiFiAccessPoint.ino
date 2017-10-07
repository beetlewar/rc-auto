#include <ESP8266WiFi.h>

bool setupAP(const char *ssid, const char *password)
{
    bool b = WiFi.softAP(ssid, password);

    if (b)
    {
        printLog("Started access point at ");
        printlnLog(WiFi.softAPIP());
    }
    else
    {
        printlnLog("Failed to start access point");
    }

    return b;
}