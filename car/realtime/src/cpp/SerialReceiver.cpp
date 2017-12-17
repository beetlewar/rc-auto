#include "Includes.h"

const int SERIAL_RX = D6;

typedef union {
    float floatingPoint;
    uint8_t binary[4];
} binaryFloat;

enum transmittionItemType
{
    WHEEL,
    GAS
};

SerialReceiver::SerialReceiver(Logger *logger, Car *car)
{
    _logger = logger;
    _car = car;
    _serial = new SoftwareSerial(SERIAL_RX, SW_SERIAL_UNUSED_PIN);
}

SerialReceiver::~SerialReceiver()
{
    delete _serial;
    _serial = NULL;
}

bool SerialReceiver::setup()
{
    _serial->begin(115200);

    _logger->print("Serial RX started at pin ");
    _logger->println(SERIAL_RX);

    return true;
}

void SerialReceiver::loop()
{
    const float invalidWheel = -100;
    const float invalidGas = -100;

    float wheel = invalidWheel;
    float gas = invalidGas;

    if (_serial->available() >= 5)
    {
        int itemType = _serial->read();

        binaryFloat value;

        for (int i = 0; i < 4; i++)
        {
            delay(0);
            value.binary[i] = _serial->read();
        }

        _logger->print("Received ");
        _logger->print(itemType == GAS ? "GAS" : "WHEEL");
        _logger->print(": ");
        _logger->println(value.floatingPoint);

        switch (itemType)
        {
        case GAS:
            gas = value.floatingPoint;
            break;
        case WHEEL:
            wheel = value.floatingPoint;
            break;
        }
    }

    if (gas != invalidGas)
    {
        _car->setGas(gas);
    }

    if (wheel != invalidWheel)
    {
        _car->setWheel(wheel);
    }
}