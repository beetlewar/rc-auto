#pragma once

#include "Includes.h"

class CarSettingsRepository
{
private:
  Logger *_logger;
  FileSystem *_fileSystem;
  CarSettingsJsonSerializer *_settingsSerializer;
  StateOwner *_stateOwner;

public:
  CarSettingsRepository(
      Logger *logger,
      FileSystem *fileSystem,
      CarSettingsJsonSerializer *settingsSerializer,
      StateOwner *stateOwner);

  bool setup();
  CarSettings getSettings();
  void saveSettings(CarSettings settings);
};