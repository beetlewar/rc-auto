#include "Includes.h"

#ifndef UNIT_TEST

bool initialized = false;

Logger *logger = NULL;
FileSystem *fileSystem = NULL;
WiFiAccessPoint *accessPoint = NULL;
WiFiRcHost *rcHost = NULL;
SerialTransmitter *transmitter = NULL;
StateOwner *stateOwner = NULL;
MessageDispatcher *messageDispatcher = NULL;
SerialSerializer *serializer = NULL;

void setup()
{
    logger = new Logger();

    serializer = new SerialSerializer();
    stateOwner = new StateOwner();
    fileSystem = new FileSystem(logger);
    accessPoint = new WiFiAccessPoint(logger);
    transmitter = new SerialTransmitter(logger);
    rcHost = new WiFiRcHost(logger, fileSystem, transmitter, stateOwner);
    messageDispatcher = new MessageDispatcher(logger, stateOwner, transmitter, serializer);

    initialized =
        logger->setup(9600) &&
        fileSystem->setup() &&
        accessPoint->setup("rc-auto", "123qwerty") &&
        transmitter->setup() &&
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
    messageDispatcher->loop();

    delay(1);
}

#endif