#include "../Includes.h"

const int joystickInputPin = A0;
const int joystickOutputX = D5;
const int joystickOutputY = D7;

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
        20,
        940,
        390,
        470);

    _joyGas = new JoystickReader(
        logger,
        joystickInputPin,
        20,
        940,
        390,
        470);
}

void carStateTick(void *pArg)
{
    CarState *car = (CarState *)pArg;
    car->loop();
}

void CarState::loop()
{
    measureGas();
    measureWheel();
}

void CarState::measureGas()
{
    digitalWrite(joystickOutputY, HIGH);

    _gas = _joyGas->read();

    digitalWrite(joystickOutputY, LOW);
}

void CarState::measureWheel()
{
    digitalWrite(joystickOutputX, HIGH);

    _wheel = _joyWheel->read();

    digitalWrite(joystickOutputX, LOW);
}

void CarState::start(int periodMSec)
{
    os_timer_setfn(&_timer, carStateTick, this);
    os_timer_arm(&_timer, periodMSec, true);
}