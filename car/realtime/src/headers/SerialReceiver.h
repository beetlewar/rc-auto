#pragma once

#include "Includes.h"

class SerialReceiver
{
private:
  Logger *_logger;
  SoftwareSerial *_serial;
  SerialPortSerializer *_serializer;
  MessageHandler *_messageHandler;

private:
  void handleMessage(uint8_t *bytes);

public:
  SerialReceiver(
      Logger *logger,
      MessageHandler *messageHandler);

  bool setup();

  void loop();
};