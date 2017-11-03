#pragma once

#include "..\..\Includes.h"

class Car
{
private:
  Logger *_logger;
  AbstractWheel *_wheel;
  AbstractEngine *_engine;

public:
  Car(Logger *logger, AbstractWheel *wheel, AbstractEngine *engine);

  void setGas(float gas);

  void setWheel(float wheel);
};