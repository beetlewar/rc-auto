#pragma once

#include "../Includes.h"

enum BlinkState
{
    BLINK_OFF = 0,
    BLINK_ON = 1
};

class SystemIndicator
{
  private:
    Logger *_logger;
    RcWiFiClient *_wifiClient;
    unsigned long _blinkTime;
    int _blinkState;

  public:
    SystemIndicator(
        Logger *logger,
        RcWiFiClient *wifiClient);

    void setup();

    void loop();

  private:
    void updateState();

    void updateIndicator();
};