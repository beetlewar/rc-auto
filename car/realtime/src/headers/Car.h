#pragma once

#include "Includes.h"

class Car
{
private:
  Logger *_logger;
  ServoWheel *_wheel;
  LedBasedEngine *_engine;

public:
  Car(Logger *logger);

  ~Car();

  bool setup();

  void setGas(float gas);

  void setWheel(float wheel);
};