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

    const RemoteCarState carState(_car->gas(), _car->wheel());
    unsigned long time = millis();
    if (shouldSendState(&carState, time))
    {
        sendState(&carState, time);
    }
}

bool CarStateSender::shouldSendState(const RemoteCarState *carState, unsigned long time)
{
    unsigned long elapsed = time - _lastSendTime;

    if (elapsed >= CAR_STATE_SYNC_PERIOD)
    {
        _logger->println("Should sync state");
        return true;
    }

    if (elapsed >= CAR_STATE_SEND_PERIOD &&
        _sentCarState.StateChanged(carState))
    {
        _logger->println("Should send state. Was: " + String(_sentCarState.Gas) + ", " + String(_sentCarState.Wheel) + ". Now: " + String(carState->Gas) + ", " + String(carState->Wheel));
        return true;
    }

    return false;
}

void CarStateSender::sendState(const RemoteCarState *carState, unsigned long time)
{
    _logger->println("Sending car state");

    _udp.beginPacket(_ip, UDP_PORT);

    uint8_t buf[sizeof(RemoteCarState)];
    unsigned long size = _serializer.serialize(carState, buf);

    _udp.write(buf, size);

    _udp.endPacket();

    _sentCarState = *carState;
    _lastSendTime = time;
}