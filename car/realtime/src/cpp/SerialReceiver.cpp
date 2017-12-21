#include "Includes.h"

const int SERIAL_RX = D6;

enum transmittionItemType
{
    WHEEL,
    GAS
};

SerialReceiver::SerialReceiver(Logger *logger, Car *car)
{
    uint16_t bufSize = sizeof(uint8_t) + sizeof(float);

    _logger = logger;
    _car = car;
    _serial = new SoftwareSerial(SERIAL_RX, SW_SERIAL_UNUSED_PIN);
    _serializer = new SerialPortSerializer(bufSize);
    _serializerData = new SerialPortData(bufSize);
}

SerialReceiver::~SerialReceiver()
{
    delete _serializerData;
    delete _serializer;
    delete _serial;
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
    while (_serial->available())
    {
        uint8_t byte = (uint8_t)_serial->read();

        _serializer->addByte(byte);

        if (_serializer->ready())
        {
            _serializer->getData(_serializerData);

            handleMessage(_serializerData->data());
        }
    }
}

void SerialReceiver::handleMessage(const uint8_t *data)
{
    uint8_t messageType = data[0];

    binaryFloat bf;
    bf.binary[0] = data[1];
    bf.binary[1] = data[2];
    bf.binary[2] = data[3];
    bf.binary[3] = data[4];

    switch (messageType)
    {
    case WHEEL:
        _car->setWheel(bf.floatingPoint);
        break;
    case GAS:
        _car->setGas(bf.floatingPoint);
        break;
    }
}