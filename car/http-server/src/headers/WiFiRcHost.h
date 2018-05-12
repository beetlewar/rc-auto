#pragma once

#include "Includes.h"

class WiFiRcHost
{
private:
  ESP8266WebServer _server;
  Logger *_logger;
  FileSystem *_fileSystem;
  SerialTransmitter *_serialTransmitter;

public:
  WiFiRcHost(Logger *logger, FileSystem *fileSystem, SerialTransmitter *serialTransmitter);

  bool setup();

  void loop();

private:
  void handleRoot();

  void handleBackgroundImage();

  void handleGasImage();

  void handleWheelImage();

  void handleAppScript();

  void handleState();

  void sendFile(String path, String contentType);

  String readFileAsString(String path);
};