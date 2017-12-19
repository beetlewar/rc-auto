#include "Includes.h"

const int WHEEL_PIN = D1;
const int ENGINE_PIN = D3;

Car::Car(Logger *logger)
{
    _logger = logger;

    _pwmHost = new PwmHost();

    Pwm *wheelPwm = _pwmHost->addPwm(WHEEL_PIN);

    Pwm *enginePwm = _pwmHost->addPwm(ENGINE_PIN);

    _wheel = new ServoWheel(_logger, wheelPwm);

    _engine = new Engine(_logger, enginePwm);
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