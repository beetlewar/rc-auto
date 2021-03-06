#pragma once

#include "Includes.h"

class SerialPortSerializer
{
private:
  Logger *_logger;

  uint8_t *_header;
  binaryShort _bodySize;
  uint8_t *_body;
  uint8_t *_tail;

  uint16_t _bufSize;

  uint8_t _state;
  unsigned int _position;

public:
  SerialPortSerializer(Logger *logger, uint16_t bufSize);

  ~SerialPortSerializer();

  void addByte(uint8_t byte);

  bool ready();

  uint8_t *getPayload();

private:
  void processHeader(uint8_t byte);
  void moveToHeader();
  bool checkHeaderSymbol();
  bool isHeaderReceived();

  void processBodySize(uint8_t byte);
  void moveToBodySize();
  bool isBodySizeReceived();

  void processBody(uint8_t byte);
  void moveToBody();
  bool isBodyReceived();

  void processTail(uint8_t byte);
  void moveToTail();
  bool checkTailSymbol();
  bool isTailReceived();

  void processDone(uint8_t byte);
  void moveToDone();
};