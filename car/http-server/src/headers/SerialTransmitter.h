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

  bool setup();

  void transmit(uint8_t *bytes, unsigned long size);

private:
  void transmitItem(uint8_t type, uint8_t *bytes, unsigned long size);

  void transmitHeader();

  void transmitBodySize(uint16_t size);

  void transmitBytes(uint8_t *bytes, unsigned long length);

  void transmitTail();
};