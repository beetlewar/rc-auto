#include "Includes.h"

WiFiAccessPoint::WiFiAccessPoint(Logger *logger)
{
    _logger = logger;
}

bool WiFiAccessPoint::setup(const char *ssid, const char *password)
{
    IPAddress ip(192, 168, 1, 1);
    IPAddress mask(255, 255, 255, 0);

    WiFi.softAPConfig(ip, ip, mask);
    bool b = WiFi.softAP(ssid, password, 10);

    if (b)
    {
        _logger->print("Started access point at ");
        _logger->println(WiFi.softAPIP().toString());
    }
    else
    {
        _logger->println("Failed to start access point");
    }

    return b;
}