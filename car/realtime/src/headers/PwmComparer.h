#pragma once

#include "Includes.h"

class PwmComparer : public std::binary_function<Pwm *, Pwm *, bool>
{
public:
  bool operator()(Pwm *lhs, Pwm *rhs);
};