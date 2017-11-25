#pragma once

#include "Includes.h"

class SerialReceiver
{
  private:
    Logger *_logger;
    Car *_car;
    SoftwareSerial *_serial;

  public:
    SerialReceiver(Logger *logger, Car *car);

    ~SerialReceiver();

    bool setup();

    void loop();
};