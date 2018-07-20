#pragma once

#include "Includes.h"

class RcWiFiClient
{
private:
  Logger *_logger;

public:
  RcWiFiClient(Logger *logger);

  void setup();

  bool ready();
};