#pragma once

#include "../Includes.h"

class CarStateSender
{
private:
  Logger *_logger;
  Car *_car;
  RcWiFiClient *_client;
  RemoteCarStateSerializer _serializer;
  RemoteCarState _sentCarState;

  WiFiUDP _udp;
  IPAddress _ip;
  unsigned long _lastSendTime;

public:
  CarStateSender(
      Logger *logger,
      Car *car,
      RcWiFiClient *client);

  void setup();

  void loop();

private:
  bool shouldSendState(const RemoteCarState *carState, unsigned long time);
  void sendState(const RemoteCarState *carState, unsigned long time);
};