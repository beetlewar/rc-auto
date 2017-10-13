#include "Includes.h"

bool initialized = false;

Logger logger;
FileSystem fileSystem(&logger);
WiFiAccessPoint accessPoint(&logger);
Car car(&logger);
WiFiRcHost rcHost(&logger, &fileSystem, &car);

void setup()
{
    initialized =
        logger.setup(9600) &&
        fileSystem.setup() &&
        accessPoint.setup("rc-auto", "123qwerty") &&
        car.setup() &&
        rcHost.setup();

    if (initialized)
    {
        logger.println("Successfully initialized.");
    }
    else
    {
        logger.println("Initialization failed.");
    }
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    rcHost.loop();
}