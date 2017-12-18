#pragma once

#include "Includes.h"

class Calibrator
{
  private:
    Servo _servo;

  public:
    void setup();
    void setWidthMuSec(int value);
};