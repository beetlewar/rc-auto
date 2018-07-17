#include "Includes.h"

SerialReceiver::SerialReceiver(
    Logger *logger,
    MessageHandler *messageHandler)
{
    _logger = logger;
    _messageHandler = messageHandler;

    _serial = new SoftwareSerial(SERIAL_PIN, SW_SERIAL_UNUSED_PIN);
    _serializer = new SerialPortSerializer(logger, sizeof(CarStateMessage));
}

bool SerialReceiver::setup()
{
    _serial->begin(SERIAL_SPEED);

    _logger->print("Serial RX started at ");
    _logger->println(SERIAL_PIN);

    return true;
}

void SerialReceiver::loop()
{
    while (_serial->available())
    {
        uint8_t byte = (uint8_t)_serial->read();

        _serializer->addByte(byte);

        if (_serializer->ready())
        {
            _messageHandler->handle(_serializer->getPayload());
        }
    }
}