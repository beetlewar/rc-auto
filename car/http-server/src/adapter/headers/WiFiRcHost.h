#pragma once

#include "..\..\Includes.h"

class WiFiRcHost
{
private:
  ESP8266WebServer _server;
  DNSServer _dnsServer;

  Logger *_logger;
  FileSystem *_fileSystem;
  I2CMaster *_i2cMaster;

public:
  WiFiRcHost(Logger *logger, FileSystem *fileSystem, I2CMaster *i2cMaster);

  bool setup();

  void loop();

private:
  void handleRoot();

  void handleBackgroundImage();

  void handleGasImage();

  void handleWheelImage();

  void handleAppScript();

  void handleGas();

  void handleWheel();

  void sendFile(String path, String contentType);

  String readFileAsString(String path);
};