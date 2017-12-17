#pragma once

#include "Includes.h"

class ServoWheel
{
  private:
    Logger *_logger;
    Pwm *_pwm;

  public:
    ServoWheel(Logger *logger, Pwm *pwm);
    void setRotation(float value);
};