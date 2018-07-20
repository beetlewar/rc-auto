#pragma once

#include "Includes.h"

class Engine
{
  private:
    Logger *_logger;
    Servo _servo;

  public:
    Engine(Logger *logger);
    void setGas(float value);
};