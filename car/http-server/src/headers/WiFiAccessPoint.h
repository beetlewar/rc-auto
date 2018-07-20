#pragma once

#include "Includes.h"

class WiFiAccessPoint
{
  private:
    Logger *_logger;

  public:
    WiFiAccessPoint(Logger *logger);

    bool setup();
};