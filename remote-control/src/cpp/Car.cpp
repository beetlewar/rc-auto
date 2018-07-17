#include "../Includes.h"

Car::Car(Logger *logger)
{
    _gas = 0;
    _wheel = 0;

    pinMode(JOYSTICK_INPUT_PIN, INPUT);
    pinMode(JOYSTICK_OUTPUT_X, OUTPUT);
    pinMode(JOYSTICK_OUTPUT_Y, OUTPUT);

    _joyWheel = new JoystickReader(
        logger,
        JOYSTICK_INPUT_PIN,
        100,
        800,
        400,
        500);

    _joyGas = new JoystickReader(
        logger,
        JOYSTICK_INPUT_PIN,
        100,
        800,
        400,
        500);
}

void Car::loop()
{
    measureGas();
    measureWheel();
}

void Car::measureGas()
{
    digitalWrite(JOYSTICK_OUTPUT_Y, HIGH);

    delay(1);

    _gas = _joyGas->read();

    digitalWrite(JOYSTICK_OUTPUT_Y, LOW);
}

void Car::measureWheel()
{
    digitalWrite(JOYSTICK_OUTPUT_X, HIGH);

    delay(1);

    _wheel = _joyWheel->read();

    digitalWrite(JOYSTICK_OUTPUT_X, LOW);
}