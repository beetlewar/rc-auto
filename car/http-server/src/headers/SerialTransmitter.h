#pragma once

#include "Includes.h"

class SerialTransmitter
{
private:
  Logger *_logger;
  SoftwareSerial *_serial;
  float _carGas;
  float _carWheel;

public:
  SerialTransmitter(Logger *logger);

  ~SerialTransmitter();

  bool setup();

  void transmitGas(float value);

  void transmitWheel(float value);

  void transmitKeepAlive();

private:
  void transmitItem(uint8_t type, uint8_t *bytes, int size);

  void transmitHeader();

  void transmitBodySize(uint16_t size);

  void transmitBody(uint8_t type, uint8_t *bytes, int size);

  void transmitTail();
};