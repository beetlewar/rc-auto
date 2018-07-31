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
CarSettingsRepository *settingsRepository = NULL;

void setup()
{
    logger = new Logger();

    serialSerializer = new SerialSerializer();
    stateOwner = new StateOwner(logger);
    fileSystem = new FileSystem(logger);
    settingsSerializer = new CarSettingsJsonSerializer(logger);
    settingsRepository = new CarSettingsRepository(logger, fileSystem, settingsSerializer, stateOwner);
    accessPoint = new WiFiAccessPoint(logger);
    transmitter = new SerialTransmitter(logger);
    messageDispatcher = new MessageDispatcher(logger, stateOwner, transmitter, serialSerializer);
    httpAdapter = new HttpAdapter(logger, fileSystem, stateOwner, settingsSerializer, settingsRepository);
    udpAdapter = new UdpAdapter(logger, stateOwner);

    initialized =
        logger->setup(9600) &&
        fileSystem->setup() &&
        settingsRepository->setup() &&
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