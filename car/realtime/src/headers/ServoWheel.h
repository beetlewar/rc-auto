#pragma once

#include "Includes.h"

class ServoWheel
{
  private:
    Logger *_logger;
    Pwm *_pwm;

  public:
    ServoWheel(Logger *logger, PwmHost *pwmHost);
    void setRotation(float value);
};