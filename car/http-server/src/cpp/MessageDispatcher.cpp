#include "Includes.h"

MessageDispatcher::MessageDispatcher(
    Logger *logger,
    StateOwner *stateOwner,
    SerialTransmitter *serialTransmitter,
    SerialSerializer *serializer)
{
    _logger = logger;
    _stateOwner = stateOwner;
    _serialTransmitter = serialTransmitter;
    _serializer = serializer;

    _lastSendTime = 0;
}

void MessageDispatcher::loop()
{
    const CarState carState = _stateOwner->getCarState();
    unsigned long time = millis();
    if (shouldSendState(&carState.State, time))
    {
        sendState(&carState, time);
    }
}

bool MessageDispatcher::shouldSendState(const RemoteCarState *carState, unsigned long time)
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

void MessageDispatcher::sendState(const CarState *carState, unsigned long time)
{
    _logger->println("Sending car state message");

    const CarStateMessage serializingMessage = CarStateMessage(
        time,
        carState->KeepAliveTime,
        carState->State.Gas,
        carState->State.Wheel);

    uint8_t buffer[sizeof(CarStateMessage)];

    unsigned long serializedLength = _serializer->serialize(&serializingMessage, buffer);

    _serialTransmitter->transmit(buffer, serializedLength);

    _sentCarState = carState->State;
    _lastSendTime = time;
}