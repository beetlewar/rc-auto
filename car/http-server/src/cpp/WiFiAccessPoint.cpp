#include "Includes.h"

WiFiAccessPoint::WiFiAccessPoint(Logger *logger)
{
    _logger = logger;
}

bool WiFiAccessPoint::setup()
{
    IPAddress ip;
    ip.fromString(WIFI_IP);
    IPAddress mask(255, 255, 255, 0);

    WiFi.softAPConfig(ip, ip, mask);
    bool b = WiFi.softAP(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str(), WIFI_HOST_CHANNEL);

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