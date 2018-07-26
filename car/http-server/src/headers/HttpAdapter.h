#pragma once

#include "Includes.h"

class HttpAdapter
{
private:
  ESP8266WebServer _server;
  Logger *_logger;
  FileSystem *_fileSystem;
  StateOwner *_stateOwner;

public:
  HttpAdapter(
      Logger *logger,
      FileSystem *fileSystem,
      StateOwner *stateOwner);

  bool setup();

  void loop();

private:
  void handleRoot();

  void handleBackgroundImage();

  void handleGasImage();

  void handleWheelImage();

  void handleAppScript();

  void handleAdminPage();

  void handleBootstrapMinCss();

  void handleBootstrapMinJs();

  void handleJQuery();

  void handlePopper();

  void handleSliderCss();

  void handleState();

  void sendFile(String path, String contentType);

  String readFileAsString(String path);
};