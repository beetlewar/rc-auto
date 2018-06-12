#pragma once

#include "../Includes.h"

class Car
{
private:
  Logger *_logger;
  JoystickReader *_joyWheel;
  JoystickReader *_joyGas;
  float _gas;
  float _wheel;

private:
  void measureGas();
  void measureWheel();

public:
  Car(Logger *logger);

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