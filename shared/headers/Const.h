#pragma once

// #define DEBUG

const String WIFI_SSID = "rc-auto";
const String WIFI_PASSWORD = "123qwerty";
const String WIFI_IP = "192.168.1.1";
const int WIFI_HOST_CHANNEL = 10;

const unsigned long CAR_STATE_SEND_PERIOD = 40;
const unsigned long CAR_STATE_SYNC_PERIOD = 200;
const unsigned long KEEP_ALIVE_TIMEOUT = 1000;

const int SERIAL_PIN = D6;
const long SERIAL_SPEED = 115200;

const int ENGINE_PIN = D3;
const float ENGINE_NEUTRAL = 1500;
const float ENGINE_MAX_BACKWARD = 1000;
const float ENGINE_MAX_FORWARD = 2000;
const float ENGINE_FORWARD_POWER = 0.5f;
const float ENGINE_BACKWARD_POWER = 0.2f;
const float ENGINE_ACCELERATION_TIME = 2000;
const float ENGINE_ACCELERATION_POWER = 0.5f;

const String TRANSPORT_HEADER_VALUE = "Hello";
const String TRANSPORT_TAIL_VALUE = "World";

const int WHEEL_PIN = D1;
const float WHEEL_MAX_ROTATION_MSEC = 300;
const float WHEEL_CENTER_ROTATION_MSEC = 1500;

const int JOYSTICK_INPUT_PIN = A0;
const int JOYSTICK_OUTPUT_X = D5;
const int JOYSTICK_OUTPUT_Y = D1;

const int BLINK_INDICATOR_PIN = D7;
const unsigned long BLINK_ON_TIMEOUT = 100;
const unsigned long BLINK_OFF_WIFI_FAIL_TIMEOUT = 300;
const unsigned long BLINK_OFF_WIFI_OK_TIMEOUT = 2000;

const int UDP_PORT = 4444;