#pragma once

#include "Includes.h"

class HttpAdapter
{
private:
  ESP8266WebServer _server;
  Logger *_logger;
  FileSystem *_fileSystem;
  StateOwner *_stateOwner;
  CarSettingsJsonSerializer *_settingsSerializer;
  CarSettingsRepository *_settingsRepository;

public:
  HttpAdapter(
      Logger *logger,
      FileSystem *fileSystem,
      StateOwner *stateOwner,
      CarSettingsJsonSerializer *settingsSerializer,
      CarSettingsRepository *settingsRepository);

  bool setup();

  void loop();

private:
  void handleRoot();

  void handleBackgroundImage();

  void handleGasImage();

  void handleWheelImage();

  void handleAppScript();

  void handleAdminPage();

  void handleJQuery();

  void handleCustomStyles();

  void handlePostState();

  void handleGetSettings();

  void handlePostSettings();

  void handlePostSettingsReset();

  void sendFile(String path, String contentType);

  String readFileAsString(String path);
};