#include "Includes.h"

MessageHandler::MessageHandler(
    Logger *logger,
    SerialSerializer *serializer,
    Car *car)
{
    _logger = logger;
    _serializer = serializer;
    _car = car;
}

void MessageHandler::handle(uint8_t *message)
{
    CarStateMessage carStateMessage = _serializer->deserialize(message);

    // _logger->println(
    //     "KAT: " + String(carStateMessage.KeepAliveTime) +
    //     ", ST: " + String(carStateMessage.ServerTime) +
    //     ", G: " + String(carStateMessage.Gas) +
    //     ", W: " + String(carStateMessage.Wheel) +
    //     ", EFP: " + String(carStateMessage.EngineForwardPower) +
    //     ", EBP: " + String(carStateMessage.EngineBackwardPower) +
    //     ", AP: " + String(carStateMessage.AccelerationPower));

    _car->setState(
        carStateMessage.KeepAliveTime,
        carStateMessage.ServerTime,
        carStateMessage.Gas,
        carStateMessage.Wheel,
        carStateMessage.EngineForwardPower,
        carStateMessage.EngineBackwardPower,
        carStateMessage.AccelerationPower);
}