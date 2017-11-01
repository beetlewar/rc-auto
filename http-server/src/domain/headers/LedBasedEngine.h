#pragma once

#include "../../Includes.h"

class LedBasedEngine : public AbstractEngine
{
  private:
    Logger *_logger;

  public:
    LedBasedEngine(Logger *logger);
    bool setup();
    virtual void setGas(float value);
};