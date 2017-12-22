#pragma once

#include "Includes.h"

class Pwm
{
  private:
    int _pin;
    unsigned int _width;
    unsigned int _highTime;

  public:
    Pwm(int pin, unsigned int width);

    int getWidth();

    void setWidth(unsigned int width);

    void setHigh();

    void waitLow();
};