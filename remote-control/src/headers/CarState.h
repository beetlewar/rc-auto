#pragma once

#include "../Includes.h"

class CarState
{
private:
  Logger *_logger;
  os_timer_t _timer;
  JoystickReader *_joyWheel;
  JoystickReader *_joyGas;
  float _gas;
  float _wheel;

private:
  void measureGas();
  void measureWheel();

public:
  CarState(Logger *logger);

  void start(int periodMSec);

  void loop();

  float gas()
  {
    return _gas;
  }

  float wheel()
  {
    return _wheel;
  }
};