#pragma once

#include "Includes.h"

class ServoWheel
{
  private:
    Logger *_logger;
    Servo _servo;

  public:
    ServoWheel(Logger *logger);
    void setRotation(float value);
};