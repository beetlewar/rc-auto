#include "Includes.h"

Logger *logger;
RcWiFiClient *wifiClient;
CarState *carState;
CarStateSender *carStateSender;
SystemIndicator *systemIndicator;

//#define HTTP_LOCAL

void setup()
{
    logger = new Logger();

#ifdef HTTP_LOCAL

    char *ssid = "beetlewar";
    char *password = "beetletong85";
    String ip = "192.168.1.70";
    int port = 8080;

#else

    char *ssid = "rc-auto";
    char *password = "123qwerty";
    String ip = "192.168.1.1";
    int port = 80;

#endif

    wifiClient = new RcWiFiClient(
        logger,
        ssid,
        password,
        ip,
        port);

    carState = new CarState(logger);

    carStateSender = new CarStateSender(logger, carState, wifiClient);

    systemIndicator = new SystemIndicator(logger, wifiClient);

    logger->setup(9600);
    wifiClient->setup();
    systemIndicator->setup();
}

void loop()
{
    if (wifiClient->ready())
    {
        carState->loop();
        carStateSender->loop();
        systemIndicator->loop();
        delay(10);
    }
    else
    {
        systemIndicator->loop();
        delay(100);
    }
}