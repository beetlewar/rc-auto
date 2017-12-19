#pragma once

#include "Includes.h"

class Engine
{
  private:
    Logger *_logger;
    Pwm *_pwm;

  public:
    Engine(Logger *logger, Pwm *pwm);
    void setGas(float value);
};