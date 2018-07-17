#pragma once

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Servo.h"

#include <vector>
#include <queue>

extern "C" {
#include "user_interface.h"
}

#include "..\..\..\shared\headers\Const.h"
#include "..\..\..\shared\headers\Unions.h"
#include "..\..\..\shared\headers\SerialSerializer.h"
#include "..\..\..\shared\headers\Logger.h"

#include "headers\Pwm.h"
#include "headers\PwmComparer.h"
#include "headers\PwmHost.h"
#include "headers\Engine.h"
#include "headers\ServoWheel.h"
#include "headers\Car.h"
#include "headers\MessageHandler.h"
#include "headers\SerialPortSerializer.h"
#include "headers\SerialReceiver.h"