#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
FileSystem *fileSystem = NULL;
WiFiAccessPoint *accessPoint = NULL;
SerialTransmitter *transmitter = NULL;
StateOwner *stateOwner = NULL;
MessageDispatcher *messageDispatcher = NULL;
SerialSerializer *serializer = NULL;
HttpAdapter *httpAdapter = NULL;
UdpAdapter *udpAdapter = NULL;

void setup()
{
    logger = new Logger();

    serializer = new SerialSerializer();
    stateOwner = new StateOwner();
    fileSystem = new FileSystem(logger);
    accessPoint = new WiFiAccessPoint(logger);
    transmitter = new SerialTransmitter(logger);
    messageDispatcher = new MessageDispatcher(logger, stateOwner, transmitter, serializer);
    httpAdapter = new HttpAdapter(logger, fileSystem, stateOwner);
    udpAdapter = new UdpAdapter(logger, stateOwner);

    initialized =
        logger->setup(9600) &&
        fileSystem->setup() &&
        accessPoint->setup() &&
        transmitter->setup() &&
        httpAdapter->setup() &&
        udpAdapter->setup();

    if (initialized)
    {
        logger->println("Successfully initialized.");
    }
    else
    {
        logger->println("Initialization failed.");
    }

    delay(1000);
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    httpAdapter->loop();
    udpAdapter->loop();
    messageDispatcher->loop();

    delay(1);
}