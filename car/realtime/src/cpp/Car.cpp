#include "Includes.h"

Car::Car(Logger *logger)
{
    _logger = logger;

    _wheel = new ServoWheel(_logger);
    _engine = new Engine(_logger);

    _lastKeepAliveTime = 0;
    _lastUpdateTime = 0;
    _lastServerTime = 0;
    _lastGas = 0;
    _lastWheel = 0;

    _state = CAR_STATE_ALIVE;
}

bool Car::setup()
{
    _engine->setGas(0);

    _wheel->setRotation(0);

    return true;
}

void Car::setState(
    unsigned long keepAliveTime,
    unsigned long serverTime,
    float gas,
    float wheel)
{
    _lastUpdateTime = millis();
    _lastKeepAliveTime = keepAliveTime;
    _lastServerTime = serverTime;
    _lastGas = gas;
    _lastWheel = wheel;
}

void Car::loop()
{
    int state = checkState();
    if (state != _state)
    {
        logStateChange(state);
        _state = state;
    }

    if (_state == CAR_STATE_ALIVE)
    {
        _engine->setGas(_lastGas);
        _wheel->setRotation(_lastWheel);
    }
    else
    {
        _engine->setGas(0);
        _wheel->setRotation(0);
    }
}

int Car::checkState()
{
    unsigned long currentTime = millis();
    unsigned long dUpdateTime = currentTime - _lastUpdateTime;

    if (dUpdateTime > KEEP_ALIVE_TIMEOUT)
    {
        return CAR_STATE_HOST_TIMEOUT;
    }

    unsigned long dKeepAliveTime = _lastServerTime - _lastKeepAliveTime;

    if (dKeepAliveTime > KEEP_ALIVE_TIMEOUT)
    {
        return CAR_STATE_CLIENT_TIMEOUT;
    }

    return CAR_STATE_ALIVE;
}

void Car::logStateChange(int state)
{
    switch (state)
    {
    case CAR_STATE_ALIVE:
        _logger->println("Keep alive received.");
        break;
    case CAR_STATE_HOST_TIMEOUT:
        _logger->println("No keep alive received from host.");
        break;
    case CAR_STATE_CLIENT_TIMEOUT:
        _logger->println("No keep alive received from client.");
        break;
    default:
        break;
    }
}
