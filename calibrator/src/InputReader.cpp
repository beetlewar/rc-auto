#include "Includes.h"

InputReader::InputReader(Calibrator *calibrator)
{
    _calibrator = calibrator;
}

void InputReader::setup()
{
    printHelp();
}

void InputReader::loop()
{
    while (Serial.available())
    {
        char c = (char)Serial.read();
        ;

        if (c == '\n')
        {
            Serial.println();

            int value = _inputString.toInt();

            // 0 получается, когда не удается преобразовать строку в Int
            if (value != 0)
            {
                _calibrator->setWidthMuSec(value);
            }

            _inputString = "";
        }

        if (isDigit(c))
        {
            Serial.print(c);

            _inputString += c;
        }
    }
}

void InputReader::printHelp()
{
    Serial.println("Input PWM width (in microseconds) and press ENTER");
}