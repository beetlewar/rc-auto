#include "Includes.h"

SerialTransmitter::SerialTransmitter(Logger *logger)
{
    _logger = logger;
    _serial = new SoftwareSerial(SW_SERIAL_UNUSED_PIN, SERIAL_PIN);
    _serial->begin(SERIAL_SPEED);
    _carGas = 0;
    _carWheel = 0;
}

bool SerialTransmitter::setup()
{
    _logger->print("Serial TX started at ");
    _logger->println(SERIAL_PIN);

    return true;
}

void SerialTransmitter::transmit(uint8_t *bytes, unsigned long size)
{
    transmitHeader();

    transmitBodySize(size);

    transmitBytes(bytes, size);

    transmitTail();
}

void SerialTransmitter::transmitHeader()
{
    _serial->print(TRANSPORT_HEADER_VALUE);
}

void SerialTransmitter::transmitBodySize(uint16_t size)
{
    binaryShort bs;
    bs.value = size;

    transmitBytes(bs.binary, sizeof(bs));
}

void SerialTransmitter::transmitBytes(uint8_t *bytes, unsigned long length)
{
    _serial->write(bytes, length);
}

void SerialTransmitter::transmitTail()
{
    _serial->print(TRANSPORT_TAIL_VALUE);
}