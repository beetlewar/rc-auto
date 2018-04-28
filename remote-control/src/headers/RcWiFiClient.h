#pragma once

#include "../Includes.h"

class RcWiFiClient
{
private:
  Logger *_logger;
  char *_ssid;
  char *_password;
  String _host;
  int _port;

private:
  void put(String uri, String content);

public:
  RcWiFiClient(
      Logger *logger,
      char *ssid,
      char *password,
      String host,
      int port);

  void setup();

  bool ready();

  void sendGas(float value);

  void sendWheel(float value);

  void sendKeepAlive();
};