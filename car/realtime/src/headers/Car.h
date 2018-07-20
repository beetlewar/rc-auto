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

  unsigned long _lastKeepAliveTime;
  unsigned long _lastServerTime;
  unsigned long _lastUpdateTime;
  float _lastGas;
  float _lastWheel;
  int _state;

public:
  Car(Logger *logger);

  bool setup();

  void loop();

  void setState(
      unsigned long keepAliveTime,
      unsigned long serverTime,
      float gas,
      float wheel);

private:
  int checkState();
  void logStateChange(int state);
};