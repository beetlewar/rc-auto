#include "Includes.h"

const int HM_TIMEOUT_MSEC = 2000;

HealthMonitor::HealthMonitor(Logger *logger, Car *car)
{
    _logger = logger;
    _car = car;
}

void hmHostTick(void *pArg)
{
    HealthMonitor *hm = (HealthMonitor *)pArg;
    hm->loop();
}

void HealthMonitor::start()
{
    _lastKeepAlive = millis();

    os_timer_setfn(&_hmTimer, hmHostTick, this);
    os_timer_arm(&_hmTimer, HM_TIMEOUT_MSEC, true);
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
    }
}

void HealthMonitor::keepAlive()
{
    _lastKeepAlive = millis();
}