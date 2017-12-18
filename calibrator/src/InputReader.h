#pragma once

#include "Includes.h"

class InputReader
{
  private:
    Calibrator *_calibrator;
    String _inputString;

  private:
    void printHelp();

  public:
    InputReader(Calibrator *calibrator);
    void setup();
    void loop();
};