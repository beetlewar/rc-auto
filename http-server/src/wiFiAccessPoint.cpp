#include "Includes.h"

WiFiAccessPoint::WiFiAccessPoint(Logger *logger)
{
    _logger = logger;
}

bool WiFiAccessPoint::setup(const char *ssid, const char *password)
{
    bool b = WiFi.softAP(ssid, password);

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