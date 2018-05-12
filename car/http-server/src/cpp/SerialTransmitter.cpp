#include "Includes.h"

const int SERIAL_TX = D6;

typedef union {
    float floatingPoint;
    uint8_t binary[4];
} binaryFloat;

typedef union {
    uint16_t shortValue;
    uint8_t binary[2];
} binaryShort;

SerialTransmitter::SerialTransmitter(Logger *logger)
{
    _logger = logger;
    _serial = new SoftwareSerial(SW_SERIAL_UNUSED_PIN, SERIAL_TX);
    _serial->begin(115200);
    _carGas = 0;
    _carWheel = 0;
}

SerialTransmitter::~SerialTransmitter()
{
    delete _serial;
    _serial = NULL;
}

bool SerialTransmitter::setup()
{
    _logger->print("Serial TX started at ");
    _logger->println(SERIAL_TX);

    return true;
}

void SerialTransmitter::transmitState(CarState *state)
{
    transmitHeader();

    transmitBodySize(sizeof(float) * 2);

    binaryFloat bfGas;
    bfGas.floatingPoint = state->gas;
    transmitBytes(bfGas.binary, sizeof(float));

    binaryFloat bfWheel;
    bfWheel.floatingPoint = state->wheel;
    transmitBytes(bfWheel.binary, sizeof(float));

    transmitTail();
}

void SerialTransmitter::transmitHeader()
{
    const String header = "Hello";

    for (int i = 0; i < header.length(); i++)
    {
        _serial->write(header[i]);
    }
}

void SerialTransmitter::transmitBodySize(uint16_t size)
{
    binaryShort bs;
    bs.shortValue = size;

    transmitBytes(bs.binary, sizeof(short));
}

void SerialTransmitter::transmitBytes(uint8_t *bytes, int length)
{
    for (int i = 0; i < length; i++)
    {
        _serial->write(bytes[i]);
    }
}

void SerialTransmitter::transmitTail()
{
    const String tail = "World";

    for (int i = 0; i < tail.length(); i++)
    {
        _serial->write(tail[i]);
    }
}