#include "Includes.h"

const int HM_TIMEOUT_MSEC = 500;

HealthMonitor::HealthMonitor(Logger *logger, Car *car)
{
    _logger = logger;
    _car = car;
}

void HealthMonitor::loop()
{
    unsigned long currentTime = millis();
    unsigned long dTime = currentTime - _lastKeepAlive;

    if (dTime > HM_TIMEOUT_MSEC)
    {
        _car->setGas(0);
        _car->setWheel(0);

        _logger->println("No keep alive received. Car is stopped.");

        _lastKeepAlive = currentTime;
    }
}

void HealthMonitor::keepAlive()
{
    _lastKeepAlive = millis();
}