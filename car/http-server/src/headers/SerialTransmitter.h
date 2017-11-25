#pragma once

#include "Includes.h"

class SerialTransmitter
{
private:
    Logger *_logger;
    SoftwareSerial *_serial;

public:
    SerialTransmitter(Logger *logger);

    ~SerialTransmitter();

    bool setup();

    void transmitGas(float value);

    void transmitWheel(float value);
};