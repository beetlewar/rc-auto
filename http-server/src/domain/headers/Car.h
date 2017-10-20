#pragma once

#include "..\..\Includes.h"

class Car
{
  private:
    Logger *_logger;
    float _gas;
    float _wheel;

  public:
    Car(Logger *logger);

    bool setup();

    void setGas(float gas);

    void setWheel(float wheel);
};