#pragma once

#include "Includes.h"

class Car
{
private:
  Logger *_logger;
  Engine *_engine;
  ServoWheel *_wheel;
  PwmHost *_pwmHost;

public:
  Car(Logger *logger);

  ~Car();

  bool setup();

  void setGas(float gas);

  void setWheel(float wheel);
};