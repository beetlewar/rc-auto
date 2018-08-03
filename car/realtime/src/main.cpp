#include "Includes.h"

bool initialized = false;

Logger *logger = NULL;
Car *car = NULL;
SerialReceiver *receiver = NULL;
SerialSerializer *serializer = NULL;
MessageHandler *messageHandler = NULL;

unsigned long sleepTime = 0;
const unsigned long WIFI_SLEEP_CHECK_INTERVAL = 50000;
const int WIFI_SLEEP_DURATION_MICROS = 100000000;

extern "C"
{
#include "user_interface.h"
}

void setup()
{
    WiFi.mode(WIFI_STA);
    wifi_set_sleep_type(MODEM_SLEEP_T);
    WiFi.forceSleepBegin(WIFI_SLEEP_DURATION_MICROS);

    logger = new Logger();
    car = new Car(logger);
    serializer = new SerialSerializer();
    messageHandler = new MessageHandler(logger, serializer, car);
    receiver = new SerialReceiver(logger, messageHandler);

    initialized =
        logger->setup(9600) &&
        car->setup() &&
        receiver->setup();

    delay(2000);
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    unsigned long time = millis();
    unsigned long elapsed = time - sleepTime;

    if (elapsed > WIFI_SLEEP_CHECK_INTERVAL)
    {
        logger->println("sleeping");
        WiFi.forceSleepBegin(WIFI_SLEEP_DURATION_MICROS);
        sleepTime = time;
    }

    receiver->loop();
    car->loop();
    delay(1);
}