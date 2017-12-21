#pragma once

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Servo.h"

#include <vector>
#include <queue>

extern "C" {
#include "user_interface.h"
}

#include "headers\Logger.h"
#include "headers\typedefs.h"
#include "headers\Pwm.h"
#include "headers\PwmComparer.h"
#include "headers\PwmHost.h"
#include "headers\Engine.h"
#include "headers\ServoWheel.h"
#include "headers\Car.h"
#include "headers\SerialPortData.h"
#include "headers\SerialPortSerializer.h"
#include "headers\SerialReceiver.h"