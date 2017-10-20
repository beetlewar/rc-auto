#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
FileSystem *fileSystem = NULL;
WiFiAccessPoint *accessPoint = NULL;
Car *car = NULL;
WiFiRcHost *rcHost = NULL;

void setup()
{
    logger = new Logger();
    fileSystem = new FileSystem(logger);
    accessPoint = new WiFiAccessPoint(logger);
    car = new Car(logger);
    rcHost = new WiFiRcHost(logger, fileSystem, car);

    initialized =
        logger->setup(9600) &&
        fileSystem->setup() &&
        accessPoint->setup("rc-auto", "123qwerty") &&
        car->setup() &&
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