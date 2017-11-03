#pragma once

#include "..\..\Includes.h"

class WiFiRcHost
{
private:
  ESP8266WebServer _server;
  DNSServer _dnsServer;

  Logger *_logger;
  FileSystem *_fileSystem;
  AbstractCarMessageHandler *_carMessageHandler;

public:
  WiFiRcHost(Logger *logger, FileSystem *fileSystem, AbstractCarMessageHandler *carMessageHandler);

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