#include "../Includes.h"

CarStateSender::CarStateSender(
    Logger *logger,
    CarState *carState,
    RcWiFiClient *client)
{
    _sentGas = -1000.0f;
    _sentWheel = -1000.0f;

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