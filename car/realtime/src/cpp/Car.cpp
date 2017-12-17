#include "Includes.h"

Car::Car(Logger *logger)
{
    _logger = logger;

    _pwmHost = new PwmHost();

    Pwm *pwm = _pwmHost->addPwm(D1);

    _wheel = new ServoWheel(_logger, pwm);
}

Car::~Car()
{
    delete _wheel;
    delete _pwmHost;
}

bool Car::setup()
{
    _logger->println("Starting servo wheel at pin D1");

    _pwmHost->start(20);

    return true;
}

void Car::setGas(float gas)
{
}

void Car::setWheel(float wheel)
{
    _wheel->setRotation(wheel);
}