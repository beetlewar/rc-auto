#pragma once

#include "../Includes.h"

class JoystickReader
{
  private:
    Logger *_logger;
    int _pin;
    int _low;
    int _high;
    int _lowMid;
    int _highMid;

  public:
    JoystickReader(
        Logger *logger,
        int pin,
        int low,
        int high,
        int lowMid,
        int highMid);

    float read();
};