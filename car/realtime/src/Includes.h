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
#include "headers\Pwm.h"
#include "headers\PwmComparer.h"
#include "headers\PwmHost.h"
#include "headers\ServoWheel.h"
#include "headers\Car.h"
#include "headers\SerialReceiver.h"