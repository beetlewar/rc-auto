#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
FileSystem *fileSystem = NULL;
WiFiAccessPoint *accessPoint = NULL;
SerialTransmitter *transmitter = NULL;
StateOwner *stateOwner = NULL;
MessageDispatcher *messageDispatcher = NULL;
SerialSerializer *serialSerializer = NULL;
HttpAdapter *httpAdapter = NULL;
UdpAdapter *udpAdapter = NULL;
CarSettingsJsonSerializer *settingsSerializer = NULL;

void setup()
{
    logger = new Logger();

    serialSerializer = new SerialSerializer();
    settingsSerializer = new CarSettingsJsonSerializer(logger);
    stateOwner = new StateOwner();
    fileSystem = new FileSystem(logger);
    accessPoint = new WiFiAccessPoint(logger);
    transmitter = new SerialTransmitter(logger);
    messageDispatcher = new MessageDispatcher(logger, stateOwner, transmitter, serialSerializer);
    httpAdapter = new HttpAdapter(logger, fileSystem, stateOwner, settingsSerializer);
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