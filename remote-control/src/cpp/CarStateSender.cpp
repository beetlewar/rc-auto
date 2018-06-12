#include "../Includes.h"

CarStateSender::CarStateSender(
    Logger *logger,
    Car *car,
    RcWiFiClient *client)
{
    _logger = logger;
    _car = car;
    _client = client;
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
    CarState state;
    state.gas = _car->gas();
    state.wheel = _car->wheel();

    _client->sendState(&state);
}