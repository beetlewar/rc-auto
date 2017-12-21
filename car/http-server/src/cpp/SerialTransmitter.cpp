#include "Includes.h"

const int SERIAL_TX = D6;
const float TRANSMITTION_ACC = 0.05f;

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
    GAS
};

SerialTransmitter::SerialTransmitter(Logger *logger)
{
    _logger = logger;
    _serial = new SoftwareSerial(SW_SERIAL_UNUSED_PIN, SERIAL_TX);
    _serial->begin(115200);

    _gas = 0;
    _wheel = 0;
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
    float dGas = abs(_gas - value);
    if (dGas < TRANSMITTION_ACC)
    {
        return;
    }

    transmitItem(GAS, value);

    _gas = value;
}

void SerialTransmitter::transmitWheel(float value)
{
    float dWheel = abs(_wheel - value);
    if (dWheel < TRANSMITTION_ACC)
    {
        return;
    }

    transmitItem(WHEEL, value);

    _wheel = value;
}

void SerialTransmitter::transmitItem(uint8_t type, float value)
{
    transmitHeader();

    transmitBodySize(sizeof(uint8_t) + sizeof(float));

    transmitBody(type, value);

    transmitTail();
}

void SerialTransmitter::transmitHeader()
{
    const String header = "Hello";

    for (int i = 0; i < header.length(); i++)
    {
        _serial->write(header[i]);
    }

    _logger->println("Hello sent");
}

void SerialTransmitter::transmitBodySize(uint16_t size)
{
    binaryShort bs;
    bs.shortValue = size;

    _serial->write(bs.binary[0]);
    _serial->write(bs.binary[1]);

    _logger->println("Size sent");
}

void SerialTransmitter::transmitBody(uint8_t type, float value)
{
    _serial->write(type);

    binaryFloat bf;
    bf.floatingPoint = value;

    _serial->write(bf.binary[0]);
    _serial->write(bf.binary[1]);
    _serial->write(bf.binary[2]);
    _serial->write(bf.binary[3]);

    _logger->println("value sent");
}

void SerialTransmitter::transmitTail()
{
    const String tail = "World";

    for (int i = 0; i < tail.length(); i++)
    {
        _serial->write(tail[i]);
    }

    _logger->println("World sent");
}