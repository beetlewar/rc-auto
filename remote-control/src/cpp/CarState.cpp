#include "../Includes.h"

const int joystickInputPin = A0;
const int joystickOutputX = D5;
const int joystickOutputY = D1;

CarState::CarState(Logger *logger)
{
    _gas = 0;
    _wheel = 0;

    pinMode(joystickInputPin, INPUT);
    pinMode(joystickOutputX, OUTPUT);
    pinMode(joystickOutputY, OUTPUT);

    _joyWheel = new JoystickReader(
        logger,
        joystickInputPin,
        100,
        800,
        400,
        500);

    _joyGas = new JoystickReader(
        logger,
        joystickInputPin,
        100,
        800,
        400,
        500);
}

void CarState::loop()
{
    measureGas();
    measureWheel();
}

void CarState::measureGas()
{
    digitalWrite(joystickOutputY, HIGH);

    delay(2);

    _gas = _joyGas->read();

    digitalWrite(joystickOutputY, LOW);
}

void CarState::measureWheel()
{
    digitalWrite(joystickOutputX, HIGH);

    delay(2);

    _wheel = _joyWheel->read();

    digitalWrite(joystickOutputX, LOW);
}