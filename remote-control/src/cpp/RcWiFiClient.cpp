#include "Includes.h"

RcWiFiClient::RcWiFiClient(Logger *logger)
{
    _logger = logger;
}

void RcWiFiClient::setup()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID.c_str(), WIFI_PASSWORD.c_str());
}

bool RcWiFiClient::ready()
{
    return WiFi.status() == WL_CONNECTED;
}