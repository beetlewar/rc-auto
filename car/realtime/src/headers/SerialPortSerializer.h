#pragma once

#include "Includes.h"

class SerialPortSerializer
{
  private:
    uint8_t *_header;
    uint8_t *_bodySize;
    uint8_t *_body;
    uint16_t _bufSize;
    uint16_t _messageSize;
    uint8_t *_tail;
    uint8_t _state;
    int _position;

  public:
    SerialPortSerializer(uint16_t bufSize);

    ~SerialPortSerializer();

    void addByte(uint8_t byte);

    bool ready();

    bool getData(SerialPortData *destination);

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