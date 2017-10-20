#pragma once

#include "../../Includes.h"

class LedBasedWheel : public AbstractWheel
{
  private:
    Logger *_logger;

  public:
    LedBasedWheel(Logger *logger);
    bool setup();
    virtual void setRotation(float value);
};