#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "..\..\shared\headers\Const.h"
#include "..\..\shared\headers\Unions.h"
#include "..\..\shared\headers\Logger.h"
#include "..\..\shared\headers\RemoteCarState.h"
#include "..\..\shared\headers\RemoteCarStateSerializer.h"

#include "headers\RcWiFiClient.h"
#include "headers\JoystickReader.h"
#include "headers\Car.h"
#include "headers\CarStateSender.h"
#include "headers\SystemIndicator.h"