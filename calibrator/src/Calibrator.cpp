#include "Includes.h"

const int SERVO_PIN = D1;

void Calibrator::setup()
{
    _servo.attach(SERVO_PIN);
}

void Calibrator::setWidthMuSec(int value)
{
    Serial.print("Setting pulse width at ");
    Serial.print(value);
    Serial.println(" microseconds.");

    _servo.writeMicroseconds(value);
}