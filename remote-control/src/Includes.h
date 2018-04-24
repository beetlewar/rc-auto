#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
}

#include "headers/Logger.h"
#include "headers/RcWiFiClient.h"
#include "headers/JoystickReader.h"
#include "headers/CarState.h"
#include "headers/CarStateSender.h"