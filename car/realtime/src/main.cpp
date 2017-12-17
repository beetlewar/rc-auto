#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
Car *car = NULL;
SerialReceiver *receiver = NULL;

void setup()
{
    logger = new Logger();
    car = new Car(logger);
    receiver = new SerialReceiver(logger, car);

    initialized =
        logger->setup(9600) &&
        car->setup() &&
        receiver->setup();
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    receiver->loop();

    delay(1);
}