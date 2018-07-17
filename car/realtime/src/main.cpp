#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
Car *car = NULL;
SerialReceiver *receiver = NULL;
SerialSerializer *serializer = NULL;
MessageHandler *messageHandler = NULL;

void setup()
{
    logger = new Logger();
    car = new Car(logger);
    serializer = new SerialSerializer();
    messageHandler = new MessageHandler(logger, serializer, car);
    receiver = new SerialReceiver(logger, messageHandler);

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
    car->loop();
    delay(1);
}