#include "Includes.h"

Logger *logger;
RcWiFiClient *wifiClient;
CarState *carState;
CarStateSender *carStateSender;

void setup()
{
    logger = new Logger();

    // wifiClient = new RcWiFiClient(
    //     logger,
    //     "beetlewar",
    //     "beetletong85",
    //     "192.168.1.70",
    //     8080);

    char *ssid = "rc-auto";
    char *password = "123qwerty";
    String ip = "192.168.1.1";
    int port = 80;

    wifiClient = new RcWiFiClient(
        logger,
        ssid,
        password,
        ip,
        port);

    carState = new CarState(logger);

    carStateSender = new CarStateSender(logger, carState, wifiClient);

    logger->setup(9600);
    wifiClient->setup();
    carState->start(10);
}

void loop()
{
    carStateSender->loop();
    delay(10);
}