#include "..\..\Includes.h"

const int gasPin = D11;

LedBasedEngine::LedBasedEngine(Logger *logger)
{
    _logger = logger;
}

bool LedBasedEngine::setup()
{
    pinMode(gasPin, OUTPUT);

    return true;
}

void LedBasedEngine::setGas(float value)
{
    int analogGas = (int)(255 * value);

    _logger->print("Setting gas to ");
    _logger->println(analogGas);

    analogWrite(gasPin, analogGas);
}