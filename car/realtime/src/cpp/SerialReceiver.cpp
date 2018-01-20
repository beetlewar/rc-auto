#include "Includes.h"

const int SERIAL_RX = D6;

enum transmittionItemType
{
    WHEEL,
    GAS,
    KEEP_ALIVE
};

SerialReceiver::SerialReceiver(Logger *logger, Car *car, HealthMonitor *hm)
{
    _logger = logger;
    _car = car;
    _hm = hm;

    uint16_t bufSize = sizeof(uint8_t) + sizeof(float);

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

void SerialReceiver::handleMessage(uint8_t *data)
{
    uint8_t messageType = data[0];
    ++data;

    switch (messageType)
    {
    case WHEEL:
    {
        float wheel = readFloat(data);
        _car->setWheel(wheel);
        break;
    }
    case GAS:
    {
        float gas = readFloat(data);
        _car->setGas(gas);
        break;
    }
    case KEEP_ALIVE:
    {
        _hm->keepAlive();
        break;
    }
    }
}

float SerialReceiver::readFloat(uint8_t *bytes)
{
    binaryFloat bf;
    bf.binary[0] = bytes[0];
    bf.binary[1] = bytes[1];
    bf.binary[2] = bytes[2];
    bf.binary[3] = bytes[3];

    return bf.floatingPoint;
}