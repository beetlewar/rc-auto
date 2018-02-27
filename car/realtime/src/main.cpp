#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
Car *car = NULL;
SerialReceiver *receiver = NULL;
HealthMonitor *hm = NULL;

void setup()
{
    logger = new Logger();
    car = new Car(logger);
    hm = new HealthMonitor(logger, car);
    receiver = new SerialReceiver(logger, car, hm);

    initialized =
        logger->setup(9600) &&
        car->setup() &&
        receiver->setup();

    hm->start();
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    receiver->loop();
}