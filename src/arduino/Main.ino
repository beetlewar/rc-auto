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