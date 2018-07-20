#include "../Includes.h"

JoystickReader::JoystickReader(
    Logger *logger,
    int pin,
    int low,
    int high,
    int lowMid,
    int highMid)
{
    _logger = logger;
    _pin = pin;
    _low = low;
    _high = high;
    _lowMid = lowMid;
    _highMid = highMid;
}

float JoystickReader::read()
{
    int val = analogRead(_pin);

    float result = 0;

    if (val > _highMid)
    {
        result = (float)(val - _highMid) / (float)(_high - _highMid);
    }
    else if (val < _lowMid)
    {
        result = (float)(val - _lowMid) / (float)(_lowMid - _low);
    }

    if (result == 0)
    {
        return result;
    }

    if (result < -1)
    {
        result = -1;
    }
    else if (result > 1)
    {
        result = 1;
    }

    float resultModified = result;

    if (result < 0)
    {
        resultModified = -resultModified;
    }

    resultModified = sqrt(resultModified);

    if (result < 0)
    {
        resultModified = -resultModified;
    }

    return resultModified;
}