#include "Includes.h"

#ifndef UNIT_TEST

bool initialized = false;

Logger *logger = NULL;
FileSystem *fileSystem = NULL;
WiFiAccessPoint *accessPoint = NULL;
AbstractCarMessageHandler *carMessageHandler = NULL;
AbstractWheel *wheel = NULL;
AbstractEngine *engine = NULL;
Car *car = NULL;
WiFiRcHost *rcHost = NULL;

void setup()
{
    logger = new Logger();

    ServoWheel *concreteWheel = new ServoWheel(logger);
    LedBasedEngine *concreteEngine = new LedBasedEngine(logger);

    wheel = concreteWheel;
    engine = concreteEngine;

    fileSystem = new FileSystem(logger);
    accessPoint = new WiFiAccessPoint(logger);
    car = new Car(logger, wheel, engine);
    carMessageHandler = new CarMessageHandler(car);
    rcHost = new WiFiRcHost(logger, fileSystem, carMessageHandler);

    initialized =
        logger->setup(9600) &&
        fileSystem->setup() &&
        accessPoint->setup("rc-auto", "123qwerty") &&
        concreteEngine->setup() &&
        concreteWheel->setup() &&
        rcHost->setup();

    if (initialized)
    {
        logger->println("Successfully initialized.");
    }
    else
    {
        logger->println("Initialization failed.");
    }
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    rcHost->loop();
}

#endif