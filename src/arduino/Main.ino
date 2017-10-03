bool initialized = false;

void setup()
{
    Serial.begin(9600);

    initialized =
        setupFileSystem() &&
        setupAP("rc-auto", "123qwerty") &&
        setupRcHost() &&
        setupCar();

    if (initialized)
    {
        Serial.println("Successfully initialized.");
    }
    else
    {
        Serial.println("Initialization failed.");
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