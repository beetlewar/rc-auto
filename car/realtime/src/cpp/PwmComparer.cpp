#include "Includes.h"

bool PwmComparer::operator()(Pwm *lhs, Pwm *rhs)
{
    return lhs->getWidth() > rhs->getWidth();
}