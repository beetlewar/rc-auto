#pragma once

#include "Includes.h"

class SerialReceiver
{
private:
  Logger *_logger;
  Car *_car;
  HealthMonitor *_hm;
  SoftwareSerial *_serial;
  SerialPortData *_serializerData;
  SerialPortSerializer *_serializer;

private:
  void handleMessage(uint8_t *data);

public:
  SerialReceiver(Logger *logger, Car *car, HealthMonitor *hm);

  ~SerialReceiver();

  bool setup();

  void loop();

  float readFloat(uint8_t *bytes);
};