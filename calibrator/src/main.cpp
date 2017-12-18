#include "Includes.h"

InputReader *inputReader;
Calibrator *calibrator;

void setup()
{
    Serial.begin(9600);

    Serial.println();

    calibrator = new Calibrator();
    inputReader = new InputReader(calibrator);

    inputReader->setup();
    calibrator->setup();
}

void loop()
{
    inputReader->loop();

    delay(10);
}