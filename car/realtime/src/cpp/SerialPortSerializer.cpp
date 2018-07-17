#include "Includes.h"

enum serializerState
{
    HEADER,
    BODY_SIZE,
    BODY,
    TAIL,
    DONE
};

SerialPortSerializer::SerialPortSerializer(
    Logger *logger,
    uint16_t bufSize)
{
    _logger = logger;
    _bufSize = bufSize;

    _header = new uint8_t[TRANSPORT_HEADER_VALUE.length()];
    _body = new uint8_t[bufSize];
    _tail = new uint8_t[TRANSPORT_TAIL_VALUE.length()];
    _state = HEADER;

    moveToHeader();
}

SerialPortSerializer::~SerialPortSerializer()
{
    delete[] _header;
    delete[] _body;
    delete[] _tail;
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

uint8_t *SerialPortSerializer::getPayload()
{
    return _body;
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
    return _header[_position] == TRANSPORT_HEADER_VALUE[_position];
}

bool SerialPortSerializer::isHeaderReceived()
{
    return _position == TRANSPORT_HEADER_VALUE.length() - 1;
}

void SerialPortSerializer::processBodySize(uint8_t byte)
{
    _position++;
    _bodySize.binary[_position] = byte;

    if (isBodySizeReceived())
    {
        if (_bodySize.value <= 0 || _bodySize.value > _bufSize)
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
    return _position == sizeof(binaryShort) - 1;
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
    return _position == (unsigned int)_bodySize.value - 1;
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
    return _tail[_position] == TRANSPORT_TAIL_VALUE[_position];
}

bool SerialPortSerializer::isTailReceived()
{
    return _position == TRANSPORT_TAIL_VALUE.length() - 1;
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