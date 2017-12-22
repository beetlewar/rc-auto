#pragma once

#include "Includes.h"

class HealthMonitor
{
  private:
    Logger *_logger;
    Car *_car;
    os_timer_t _hmTimer;
    unsigned long _lastKeepAlive;

  public:
    HealthMonitor(Logger *logger, Car *car);

    void start();

    void loop();

    void keepAlive();
};