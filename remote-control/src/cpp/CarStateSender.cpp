#include "../Includes.h"

CarStateSender::CarStateSender(
    Logger *logger,
    Car *car,
    RcWiFiClient *client)
{
    _logger = logger;
    _car = car;
    _client = client;

    _lastSendTime = 0;
    _ip.fromString(WIFI_IP);
}

void CarStateSender::setup()
{
    _udp.begin(UDP_PORT);
}

void CarStateSender::loop()
{
    if (!_client->ready())
    {
        return;
    }

    sendState();
}

void CarStateSender::sendState()
{
    unsigned long time = millis();
    unsigned long elapsed = time - _lastSendTime;

    if (elapsed < REMOTE_CAR_STATE_SEND_PERIOD)
    {
        return;
    }

    _logger->println("Sending car state");

    _udp.beginPacket(_ip, UDP_PORT);

    RemoteCarState carState(_car->gas(), _car->wheel());

    uint8_t buf[sizeof(RemoteCarState)];
    unsigned long size = _serializer.serialize(carState, buf);

    _udp.write(buf, size);

    _udp.endPacket();

    _lastSendTime = time;
}