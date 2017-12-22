#pragma once

#include "Includes.h"

class Engine
{
  private:
    Logger *_logger;
    Pwm *_pwm;

  public:
    Engine(Logger *logger, PwmHost *pwmHost);
    void setGas(float value);
};