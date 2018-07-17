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
  uint8_t *_serialBuffer;

public:
  MessageDispatcher(
      Logger *logger,
      StateOwner *stateOwner,
      SerialTransmitter *serialTransmitter,
      SerialSerializer *serializer);

  void loop();
};