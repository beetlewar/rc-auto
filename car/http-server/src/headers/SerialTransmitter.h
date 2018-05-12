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

  void transmitState(CarState *state);

private:
  void transmitItem(uint8_t type, uint8_t *bytes, int size);

  void transmitHeader();

  void transmitBodySize(uint16_t size);

  void transmitBytes(uint8_t *bytes, int length);

  void transmitTail();
};