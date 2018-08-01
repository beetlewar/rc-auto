#pragma once

#include "Includes.h"

enum CAR_STATE
{
  CAR_STATE_ALIVE = 0,
  CAR_STATE_HOST_TIMEOUT = 1,
  CAR_STATE_CLIENT_TIMEOUT = 2
};

class Car
{
private:
  Logger *_logger;
  Engine *_engine;
  ServoWheel *_wheel;

  Accelerator *_accelerator;
  float _accelerationPower;

  unsigned long _lastLoopTime;
  unsigned long _lastKeepAliveTime;
  unsigned long _lastServerTime;
  unsigned long _lastUpdateTime;
  float _lastGas;
  float _lastWheel;
  float _forwardPower;
  float _backwardPower;
  int _state;

public:
  Car(Logger *logger);

  bool setup();

  void loop();

  void setState(
      unsigned long keepAliveTime,
      unsigned long serverTime,
      float gas,
      float wheel,
      float forwardPower,
      float backwardPower,
      float accelerationPower);

private:
  int checkState();
  void logStateChange(int state);
  float accelerate();
  bool gasIncreased(float gas, float acceleratedGas);
};