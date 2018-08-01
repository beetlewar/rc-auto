#include "Includes.h"

Car::Car(Logger *logger)
{
    _accelerator = new Accelerator(logger);

    _logger = logger;

    _wheel = new ServoWheel(_logger);
    _engine = new Engine(_logger);

    _lastLoopTime = 0;
    _lastKeepAliveTime = 0;
    _lastUpdateTime = 0;
    _lastServerTime = 0;
    _lastGas = 0;
    _lastWheel = 0;

    _forwardPower = ENGINE_FORWARD_POWER;
    _backwardPower = ENGINE_BACKWARD_POWER;
    _accelerationPower = ENGINE_ACCELERATION_POWER;

    _state = CAR_STATE_ALIVE;
}

bool Car::setup()
{
    _engine->setGas(0, 0, 0);

    _wheel->setRotation(0);

    return true;
}

void Car::setState(
    unsigned long keepAliveTime,
    unsigned long serverTime,
    float gas,
    float wheel,
    float forwardPower,
    float backwardPower,
    float accelerationPower)
{
    _lastUpdateTime = millis();
    _lastKeepAliveTime = keepAliveTime;
    _lastServerTime = serverTime;
    _lastGas = gas;
    _lastWheel = wheel;
    _forwardPower = forwardPower;
    _backwardPower = backwardPower;
    _accelerationPower = accelerationPower;
}

void Car::loop()
{
    unsigned long time = millis();
    unsigned long elapsed = time - _lastLoopTime;

    if (elapsed < CAR_STATE_SEND_PERIOD)
    {
        return;
    }

    int state = checkState();
    if (state != _state)
    {
        logStateChange(state);
        _state = state;
    }

    if (_state == CAR_STATE_ALIVE)
    {
        float gas = _accelerator->accelerate(_lastGas, _accelerationPower);

        // _logger->println(gas);

        _engine->setGas(gas, _forwardPower, _backwardPower);

        _wheel->setRotation(_lastWheel);
    }
    else
    {
        _engine->setGas(0, 0, 0);
        _wheel->setRotation(0);
    }

    _lastLoopTime = time;
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
