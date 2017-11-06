#include "Includes.h"

#ifndef UNIT_TEST

bool initialized = false;

Logger *logger = NULL;
FileSystem *fileSystem = NULL;
WiFiAccessPoint *accessPoint = NULL;
WiFiRcHost *rcHost = NULL;
I2CMaster *i2cMaster = NULL;

void setup()
{
    logger = new Logger();

    fileSystem = new FileSystem(logger);
    i2cMaster = new I2CMaster(logger);
    accessPoint = new WiFiAccessPoint(logger);
    rcHost = new WiFiRcHost(logger, fileSystem, i2cMaster);

    initialized =
        logger->setup(9600) &&
        fileSystem->setup() &&
        accessPoint->setup("rc-auto", "123qwerty") &&
        rcHost->setup() &&
        i2cMaster->setup();

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