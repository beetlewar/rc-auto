#pragma once

#include "..\..\Includes.h"

class WiFiRcHost
{
private:
  ESP8266WebServer _server;
  DNSServer _dnsServer;

  Logger *_logger;
  FileSystem *_fileSystem;
  Car *_car;

public:
  WiFiRcHost(Logger *logger, FileSystem *fileSystem, Car *car);

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