#pragma once

#include "Includes.h"

class PwmHost
{
private:
  std::vector<Pwm *> _pwms;
  std::priority_queue<Pwm *, std::vector<Pwm *>, PwmComparer> _pwmsToModulate;
  os_timer_t _pwmTimer;

public:
  ~PwmHost();

  Pwm *addPwm(int pin, unsigned int width);

  void start(int periodMSec);

  void loop();

private:
  void setAllHigh();
  void waitAllLow();
};