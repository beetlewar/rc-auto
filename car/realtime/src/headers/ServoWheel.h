#pragma once

#include "Includes.h"

class ServoWheel
{
  private:
    Servo _servo;
    Logger *_logger;

  public:
    ServoWheel(Logger *logger);
    bool setup();
    void setRotation(float value);
};