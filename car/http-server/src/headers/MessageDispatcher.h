#pragma once

#include "Includes.h"

class MessageDispatcher
{
private:
  Logger *_logger;
  StateOwner *_stateOwner;
  SerialTransmitter *_serialTransmitter;
  SerialSerializer *_serializer;
  unsigned long _lastSendTime;
  RemoteCarState _sentCarState;

public:
  MessageDispatcher(
      Logger *logger,
      StateOwner *stateOwner,
      SerialTransmitter *serialTransmitter,
      SerialSerializer *serializer);

  void loop();

  private:
  bool shouldSendState(RemoteCarState *carState, unsigned long time);
  void sendState(CarState *carState, CarSettings *settings,unsigned long time);
};