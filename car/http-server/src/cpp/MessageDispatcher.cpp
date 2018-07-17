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
    _serialBuffer = new uint8_t[sizeof(CarStateMessage)];
}

void MessageDispatcher::loop()
{
    unsigned long serverTime = millis();
    unsigned long elapsed = serverTime - _lastSendTime;

    if (elapsed > CAR_STATE_SEND_PERIOD)
    {
        _logger->println("Sending car state message");

        CarState carState = _stateOwner->getCarState();

        CarStateMessage serializingMessage = CarStateMessage(
            serverTime,
            carState.keepAliveTime(),
            carState.gas(),
            carState.wheel());

        unsigned long serializedLength = _serializer->serialize(serializingMessage, _serialBuffer);

        _serialTransmitter->transmit(_serialBuffer, serializedLength);

        _lastSendTime = serverTime;
    }
}