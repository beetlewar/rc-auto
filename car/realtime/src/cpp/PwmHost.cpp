#include "Includes.h"

PwmHost::~PwmHost()
{
    for (std::vector<Pwm *>::iterator it = _pwms.begin(); it != _pwms.end(); it++)
    {
        delete *it;
    }

    _pwms.clear();
}

Pwm *PwmHost::addPwm(int pin, unsigned int width)
{
    Pwm *pwm = new Pwm(pin, width);

    _pwms.push_back(pwm);

    return pwm;
}

void pwmHostTick(void *pArg)
{
    PwmHost *pwm = (PwmHost *)pArg;
    pwm->loop();
}

void PwmHost::start(int periodMSec)
{
    os_timer_setfn(&_pwmTimer, pwmHostTick, this);
    os_timer_arm(&_pwmTimer, periodMSec, true);
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