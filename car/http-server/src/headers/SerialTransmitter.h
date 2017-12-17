#pragma once

#include "Includes.h"

class SerialTransmitter
{
  private:
    Logger *_logger;
    SoftwareSerial *_serial;
    float _gas;
    float _wheel;

  public:
    SerialTransmitter(Logger *logger);

    ~SerialTransmitter();

    bool setup();

    void transmitGas(float value);

    void transmitWheel(float value);

  private:
    void transmitItem(uint8_t type, float value);
};