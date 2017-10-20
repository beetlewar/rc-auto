#pragma once

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "FS.h"
#include "DNSServer.h"

#include "adapter\headers\Logger.h"
#include "domain\headers\Car.h"
#include "application\headers\AbstractCarMessageHandler.h"
#include "application\headers\CarMessageHandler.h"
#include "adapter\headers\FileSystem.h"
#include "adapter\headers\WiFiAccessPoint.h"
#include "adapter\headers\WiFiRcHost.h"