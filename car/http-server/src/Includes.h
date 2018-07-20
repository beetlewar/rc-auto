#pragma once

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "WiFiUdp.h"
#include "FS.h"
#include "SoftwareSerial.h"

#include "..\..\..\shared\headers\Const.h"
#include "..\..\..\shared\headers\Unions.h"
#include "..\..\..\shared\headers\SerialSerializer.h"
#include "..\..\..\shared\headers\Logger.h"

#include "headers\CarState.h"
#include "headers\StateOwner.h"
#include "headers\SerialTransmitter.h"
#include "headers\MessageDispatcher.h"
#include "headers\FileSystem.h"
#include "headers\WiFiAccessPoint.h"
#include "headers\WiFiRcHost.h"