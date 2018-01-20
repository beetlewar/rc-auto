#include "Includes.h"

const int SERIAL_TX = D6;
const float FLOAT_ACC = 0.01;

typedef union {
    float floatingPoint;
    uint8_t binary[4];
} binaryFloat;

typedef union {
    uint16_t shortValue;
    uint8_t binary[2];
} binaryShort;

enum transmittionItemType
{
    WHEEL,
    GAS,
    KEEP_ALIVE
};

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

void SerialTransmitter::transmitGas(float value)
{
    if (abs(value > 1))
    {
        return;
    }

    float delta = abs(_carGas - value);
    if (delta < FLOAT_ACC)
    {
        return;
    }

    binaryFloat bf;
    bf.floatingPoint = value;

    transmitItem(GAS, bf.binary, sizeof(float));

    _carGas = value;
}

void SerialTransmitter::transmitWheel(float value)
{
    if (abs(value > 1))
    {
        return;
    }

    float delta = abs(_carWheel - value);
    if (delta < FLOAT_ACC)
    {
        return;
    }

    binaryFloat bf;
    bf.floatingPoint = value;

    transmitItem(WHEEL, bf.binary, sizeof(float));

    _carWheel = value;
}

void SerialTransmitter::transmitKeepAlive()
{
    transmitItem(KEEP_ALIVE, NULL, 0);
}

void SerialTransmitter::transmitItem(uint8_t type, uint8_t *bytes, int size)
{
    transmitHeader();

    transmitBodySize(sizeof(uint8_t) + size);

    transmitBody(type, bytes, size);

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

    _serial->write(bs.binary[0]);
    _serial->write(bs.binary[1]);
}

void SerialTransmitter::transmitBody(uint8_t type, uint8_t *bytes, int size)
{
    _serial->write(type);

    for (int i = 0; i < size; i++)
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