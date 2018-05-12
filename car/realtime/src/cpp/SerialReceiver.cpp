#include "Includes.h"

const int SERIAL_RX = D6;

SerialReceiver::SerialReceiver(Logger *logger, Car *car, HealthMonitor *hm)
{
    _logger = logger;
    _car = car;
    _hm = hm;

    uint16_t bufSize = sizeof(float) * 2;

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
            _serializer->pushState(_serializerData);

            handleMessage(_serializerData->data());
        }
    }
}

void SerialReceiver::handleMessage(uint8_t *bytes)
{
    float gas = readFloat(&bytes);
    _car->setGas(gas);

    float wheel = readFloat(&bytes);
    _car->setWheel(wheel);

    _hm->keepAlive();
}

float SerialReceiver::readFloat(uint8_t **bytes)
{
    binaryFloat bf;
    bf.binary[0] = **bytes;
    (*bytes)++;
    bf.binary[1] = **bytes;
    (*bytes)++;
    bf.binary[2] = **bytes;
    (*bytes)++;
    bf.binary[3] = **bytes;
    (*bytes)++;
    // bf.binary[0] = bytes[0];
    // bf.binary[1] = bytes[1];
    // bf.binary[2] = bytes[2];
    // bf.binary[3] = bytes[3];

    return bf.floatingPoint;
}