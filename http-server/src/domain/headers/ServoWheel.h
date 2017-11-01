#pragma once

#include "../../Includes.h"

class ServoWheel : public AbstractWheel
{
  private:
    Servo _servo;
    Logger *_logger;

  public:
    ServoWheel(Logger *logger);
    bool setup();
    virtual void setRotation(float value);
};