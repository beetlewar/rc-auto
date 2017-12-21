#include "Includes.h"

enum serializerState
{
    HEADER,
    BODY_SIZE,
    BODY,
    TAIL,
    DONE
};

const String HEADER_VALUE = "Hello";
const String TAIL_VALUE = "World";

SerialPortSerializer::SerialPortSerializer(uint16_t bufSize)
{
    _header = new uint8_t[HEADER_VALUE.length()];
    _bodySize = new uint8_t[sizeof(uint16_t)];
    _body = new uint8_t[bufSize];
    _bufSize = bufSize;
    _tail = new uint8_t[TAIL_VALUE.length()];
    _state = HEADER;

    moveToHeader();
}

SerialPortSerializer::~SerialPortSerializer()
{
}

void SerialPortSerializer::addByte(uint8_t byte)
{
    switch (_state)
    {
    case HEADER:
        processHeader(byte);
        break;

    case BODY_SIZE:
        processBodySize(byte);
        break;

    case BODY:
        processBody(byte);
        break;

    case TAIL:
        processTail(byte);
        break;

    case DONE:
        processDone(byte);
        break;
    }
}

bool SerialPortSerializer::ready()
{
    return _state == DONE;
}

bool SerialPortSerializer::getData(SerialPortData *destination)
{
    if (!ready())
    {
        return false;
    }

    destination->size = _messageSize;
    memcpy(destination->data, _body, _messageSize);

    return true;
}

void SerialPortSerializer::processHeader(uint8_t byte)
{
    _position++;
    _header[_position] = byte;

    if (!checkHeaderSymbol())
    {
        moveToHeader();
    }
    else if (isHeaderReceived())
    {
        moveToBodySize();
    }
}

void SerialPortSerializer::moveToHeader()
{
    _state = HEADER;
    _position = -1;
}

bool SerialPortSerializer::checkHeaderSymbol()
{
    return _header[_position] == HEADER_VALUE[_position];
}

bool SerialPortSerializer::isHeaderReceived()
{
    return _position == HEADER_VALUE.length() - 1;
}

void SerialPortSerializer::processBodySize(uint8_t byte)
{
    _position++;
    _bodySize[_position] = byte;

    if (isBodySizeReceived())
    {
        _messageSize = *(uint16_t *)(_bodySize);

        if (_messageSize > _bufSize)
        {
            moveToHeader();
        }
        else
        {
            moveToBody();
        }
    }
}

void SerialPortSerializer::moveToBodySize()
{
    _state = BODY_SIZE;
    _position = -1;
}

bool SerialPortSerializer::isBodySizeReceived()
{
    return _position == sizeof(uint16_t) - 1;
}

void SerialPortSerializer::processBody(uint8_t byte)
{
    _position++;
    _body[_position] = byte;

    if (isBodyReceived())
    {
        moveToTail();
    }
}

void SerialPortSerializer::moveToBody()
{
    _state = BODY;
    _position = -1;
}

bool SerialPortSerializer::isBodyReceived()
{
    return _position == _messageSize - 1;
}

void SerialPortSerializer::processTail(uint8_t byte)
{
    _position++;
    _tail[_position] = byte;

    if (!checkTailSymbol())
    {
        moveToHeader();
    }
    else if (isTailReceived())
    {
        moveToDone();
    }
}

void SerialPortSerializer::moveToTail()
{
    _state = TAIL;
    _position = -1;
}

bool SerialPortSerializer::checkTailSymbol()
{
    return _tail[_position] == TAIL_VALUE[_position];
}

bool SerialPortSerializer::isTailReceived()
{
    return _position == TAIL_VALUE.length() - 1;
}

void SerialPortSerializer::processDone(uint8_t byte)
{
    moveToHeader();
    processHeader(byte);
}

void SerialPortSerializer::moveToDone()
{
    _state = DONE;
}