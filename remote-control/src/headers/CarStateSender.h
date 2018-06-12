#pragma once

#include "../Includes.h"

class CarStateSender
{
private:
  Logger *_logger;
  Car *_car;
  RcWiFiClient *_client;
  float _sentGas;
  float _sentWheel;
  unsigned long _lastKeepAliveTime;

public:
  CarStateSender(
      Logger *logger,
      Car *car,
      RcWiFiClient *client);

  void loop();

private:
  void sendState();
};