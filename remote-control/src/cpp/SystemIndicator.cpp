#include "../Includes.h"

SystemIndicator::SystemIndicator(
    Logger *logger,
    RcWiFiClient *wifiClient)
{
    _blinkState = BLINK_OFF;
    _blinkTime = 0;
    _logger = logger;
    _wifiClient = wifiClient;
}

void SystemIndicator::setup()
{
    pinMode(BLINK_INDICATOR_PIN, OUTPUT);
}

void SystemIndicator::loop()
{
    updateState();
    updateIndicator();
}

void SystemIndicator::updateState()
{
    unsigned long time = millis();
    unsigned long elapsed = time - _blinkTime;

    switch (_blinkState)
    {
    case BLINK_ON:
        if (elapsed > BLINK_ON_TIMEOUT)
        {
            _blinkTime = time;
            _blinkState = BLINK_OFF;
        }
        break;
    case BLINK_OFF:
        unsigned long timeout = _wifiClient->ready()
                           ? BLINK_OFF_WIFI_OK_TIMEOUT
                           : BLINK_OFF_WIFI_FAIL_TIMEOUT;

        if (elapsed > timeout)
        {
            _blinkTime = time;
            _blinkState = BLINK_ON;
        }
        break;
    }
}

void SystemIndicator::updateIndicator()
{
    switch (_blinkState)
    {
    case BLINK_ON:
        analogWrite(BLINK_INDICATOR_PIN, 255);
        break;
    case BLINK_OFF:
        analogWrite(BLINK_INDICATOR_PIN, 0);
        break;
    }
}