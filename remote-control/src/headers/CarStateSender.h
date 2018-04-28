#pragma once

#include "../Includes.h"

class CarStateSender
{
private:
  Logger *_logger;
  CarState *_carState;
  RcWiFiClient *_client;
  float _sentGas;
  float _sentWheel;
  unsigned long _lastKeepAliveTime;

public:
  CarStateSender(
      Logger *logger,
      CarState *carState,
      RcWiFiClient *client);

  void loop();

private:
  void sendGas();
  void sendWheel();
  void sendKeepAlive();
};