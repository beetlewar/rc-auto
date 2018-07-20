#include "Includes.h"

Logger *logger;
RcWiFiClient *wifiClient;
Car *car;
CarStateSender *carStateSender;
SystemIndicator *systemIndicator;

void setup()
{
    logger = new Logger();
    wifiClient = new RcWiFiClient(logger);
    car = new Car(logger);
    carStateSender = new CarStateSender(logger, car, wifiClient);
    systemIndicator = new SystemIndicator(logger, wifiClient);

    logger->setup(9600);
    wifiClient->setup();
    systemIndicator->setup();
    carStateSender->setup();
}

void loop()
{
    if (!wifiClient->ready())
    {
        delay(100);
    }

    car->loop();
    carStateSender->loop();
    systemIndicator->loop();
}