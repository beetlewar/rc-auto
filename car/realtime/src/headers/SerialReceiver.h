#pragma once

#include "Includes.h"

class SerialReceiver
{
private:
  Logger *_logger;
  Car *_car;
  SoftwareSerial *_serial;
  SerialPortData *_serializerData;
  SerialPortSerializer *_serializer;

private:
  void handleMessage(const uint8_t *data);

public:
  SerialReceiver(Logger *logger, Car *car);

  ~SerialReceiver();

  bool setup();

  void loop();
};