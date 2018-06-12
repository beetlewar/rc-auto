#pragma once

#include "Includes.h"

class HealthMonitor
{
  private:
    Logger *_logger;
    Car *_car;
    unsigned long _lastKeepAlive;

  public:
    HealthMonitor(Logger *logger, Car *car);

    void loop();

    void keepAlive();
};