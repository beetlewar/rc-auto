#include "ESP8266WiFi.h"

extern void printLog(String s);
extern void printlnLog(String s);

bool setupAP(const char *ssid, const char *password)
{
    bool b = WiFi.softAP(ssid, password);

    if (b)
    {
        printLog("Started access point at ");
        printlnLog(WiFi.softAPIP().toString());
    }
    else
    {
        printlnLog("Failed to start access point");
    }

    return b;
}