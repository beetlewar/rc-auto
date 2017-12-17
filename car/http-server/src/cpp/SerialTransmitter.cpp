#include "Includes.h"

const int SERIAL_TX = D6;
const float TRANSMITTION_ACC = 0.05f;

typedef union {
    float floatingPoint;
    uint8_t binary[4];
} binaryFloat;

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
    int sent = _serial->write(type);

    binaryFloat bf;
    bf.floatingPoint = value;

    sent &= _serial->write(bf.binary[0]);
    sent &= _serial->write(bf.binary[1]);
    sent &= _serial->write(bf.binary[2]);
    sent &= _serial->write(bf.binary[3]);

    _logger->print("Transmittion result for ");
    _logger->print(type);
    _logger->print(": ");
    _logger->println(sent);
}