#include "../Includes.h"

const unsigned long KEEP_ALIVE_INTERVAL = 1000;

CarStateSender::CarStateSender(
    Logger *logger,
    CarState *carState,
    RcWiFiClient *client)
{
    _sentGas = -1000.0f;
    _sentWheel = -1000.0f;
    _lastKeepAliveTime = -KEEP_ALIVE_INTERVAL;

    _logger = logger;
    _carState = carState;
    _client = client;
}

void CarStateSender::loop()
{
    if (!_client->ready())
    {
        return;
    }

    sendGas();

    sendWheel();

    sendKeepAlive();
}

void CarStateSender::sendGas()
{
    float gas = _carState->gas();
    float gasDelta = gas - _sentGas;

    if (gasDelta < 0)
    {
        gasDelta = -gasDelta;
    }

    if (gasDelta > 0.01f)
    {
        _client->sendGas(gas);
        _sentGas = gas;
    }
}

void CarStateSender::sendWheel()
{
    float wheel = _carState->wheel();
    float wheelDelta = wheel - _sentWheel;

    if (wheelDelta < 0)
    {
        wheelDelta = -wheelDelta;
    }

    if (wheelDelta > 0.01f)
    {
        _client->sendWheel(wheel);
        _sentWheel = wheel;
    }
}

void CarStateSender::sendKeepAlive()
{
    unsigned long currentTime = millis();

    unsigned long elapsed = currentTime - _lastKeepAliveTime;

    if(elapsed >= KEEP_ALIVE_INTERVAL)
    {
        _client->sendKeepAlive();
        _lastKeepAliveTime = currentTime;
    }
}