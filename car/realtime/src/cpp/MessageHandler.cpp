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

    _logger->println(
        String(carStateMessage.KeepAliveTime) +
        ", " + String(carStateMessage.ServerTime) +
        ", " + String(carStateMessage.Gas) +
        ", " + String(carStateMessage.Wheel));

    _car->setState(
        carStateMessage.KeepAliveTime,
        carStateMessage.ServerTime,
        carStateMessage.Gas,
        carStateMessage.Wheel);
}