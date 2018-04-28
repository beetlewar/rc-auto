#include "../Includes.h"

RcWiFiClient::RcWiFiClient(
    Logger *logger,
    char *ssid,
    char *password,
    String host,
    int port)
{
    _logger = logger;
    _ssid = ssid;
    _password = password;
    _host = host;
    _port = port;
}

void RcWiFiClient::setup()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
}

bool RcWiFiClient::ready()
{
    return WiFi.status() == WL_CONNECTED;
}

void RcWiFiClient::sendGas(float value)
{
    String content = "gas=" + String(value);

    put("/api/gas", content);
}

void RcWiFiClient::sendWheel(float value)
{
    String content = "wheel=" + String(value);

    put("/api/wheel", content);
}

void RcWiFiClient::sendKeepAlive()
{
    put("/api/keepAlive", "hello=world");
}

void RcWiFiClient::put(String uri, String content)
{
    WiFiClient client;
    if (!client.connect(_host, _port))
    {
        _logger->println(String("Failed to connect to host ") + _host + ": " + _port);
        return;
    }

    String request = String("PUT " + uri + " HTTP/1.1\r\n") +
                     "Content-Type: application/x-www-form-urlencoded\r\n" +
                     "Content-Length: " + content.length() + "\r\n\r\n" +
                     content + "\r\n";

    client.print(request);
    client.stopAll();
}