#include "Includes.h"

Car::Car(Logger *logger)
{
    _logger = logger;

    _pwmHost = new PwmHost();

    _wheel = new ServoWheel(_logger, _pwmHost);

    _engine = new Engine(_logger, _pwmHost);
}

Car::~Car()
{
    delete _wheel;
    delete _engine;
    delete _pwmHost;
}

bool Car::setup()
{
    _logger->println("Starting servo wheel at pin D1");

    _logger->println("Starting engine at pin D3");

    _pwmHost->start(20);

    _engine->setGas(0);

    _wheel->setRotation(0);

    return true;
}

void Car::setGas(float gas)
{
    _engine->setGas(gas);
}

void Car::setWheel(float wheel)
{
    _wheel->setRotation(wheel);
}