#pragma once

#include "Includes.h"

class Car
{
private:
  Logger *_logger;
  ServoWheel *_wheel;
  PwmHost *_pwmHost;

public:
  Car(Logger *logger);

  ~Car();

  bool setup();

  void setGas(float gas);

  void setWheel(float wheel);
};