#pragma once

#include "Includes.h"

class LedBasedEngine
{
  private:
    Logger *_logger;

  public:
    LedBasedEngine(Logger *logger);
    bool setup();
    void setGas(float value);
};