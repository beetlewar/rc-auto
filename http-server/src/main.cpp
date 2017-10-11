#include "Arduino.h"

extern bool setupLog();
extern bool setupFileSystem();
extern bool setupAP(const char *ssid, const char *password);
extern bool setupRcHost();
extern bool setupCar();
extern void printLog(String s);
extern void printlnLog(String s);
extern void loopRcHost();

bool initialized = false;

void setup()
{
    initialized =
        setupLog() &&
        setupFileSystem() &&
        setupAP("rc-auto", "123qwerty") &&
        setupRcHost() &&
        setupCar();

    if (initialized)
    {
        printlnLog("Successfully initialized.");
    }
    else
    {
        printlnLog("Initialization failed.");
    }
}

void loop()
{
    if (!initialized)
    {
        return;
    }

    loopRcHost();
}