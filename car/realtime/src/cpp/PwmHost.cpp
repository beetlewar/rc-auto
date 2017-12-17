#include "Includes.h"

PwmHost::~PwmHost()
{
    for (std::vector<Pwm *>::iterator it = _pwms.begin(); it != _pwms.end(); it++)
    {
        delete *it;
    }

    _pwms.clear();
}

Pwm *PwmHost::addPwm(int pin)
{
    Pwm *pwm = new Pwm(pin);

    _pwms.push_back(pwm);

    return pwm;
}

void tick(void *pArg)
{
    PwmHost *pwm = (PwmHost *)pArg;
    pwm->loop();
}

void PwmHost::start(int periodMSec)
{
    os_timer_setfn(&myTimer, tick, this);
    os_timer_arm(&myTimer, periodMSec, true);
}

void PwmHost::loop()
{
    setAllHigh();

    waitAllLow();
}

void PwmHost::setAllHigh()
{
    for (std::vector<Pwm *>::iterator it = _pwms.begin(); it != _pwms.end(); it++)
    {
        (*it)->setHigh();
        _pwmsToModulate.push(*it);
    }
}

void PwmHost::waitAllLow()
{
    while (!_pwmsToModulate.empty())
    {
        Pwm *pwm = _pwmsToModulate.top();

        pwm->waitLow();

        _pwmsToModulate.pop();
    }
}