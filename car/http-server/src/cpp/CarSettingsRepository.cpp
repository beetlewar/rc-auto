#include "Includes.h"

const String SETTINGS_PATH = "/settings.json";

CarSettingsRepository::CarSettingsRepository(
    Logger *logger,
    FileSystem *fileSystem,
    CarSettingsJsonSerializer *settingsSerializer,
    StateOwner *stateOwner)
{
    _logger = logger;
    _fileSystem = fileSystem;
    _settingsSerializer = settingsSerializer;
    _stateOwner = stateOwner;
}

bool CarSettingsRepository::setup()
{
    CarSettings settings = getSettings();

    _stateOwner->setCarSettings(settings);

    _logger->println("Settings repository successfully initialized");

    return true;
}

CarSettings CarSettingsRepository::getSettings()
{
    File settingsFile = _fileSystem->openRead(SETTINGS_PATH);

    if (!settingsFile || settingsFile.size() == 0)
    {
        return _stateOwner->getCarSettings();
    }

    String settingsJsonString = settingsFile.readStringUntil('\0');

    _logger->println("Deserialized settings: " + settingsJsonString);

    CarSettings deserializedSettings = _settingsSerializer->deserializeCarSettings(settingsJsonString);

    CarSettings mergedSettings = _stateOwner->getCarSettings().merge(deserializedSettings);

    return mergedSettings;
}

void CarSettingsRepository::saveSettings(CarSettings settings)
{
    CarSettings currentSettings = getSettings();

    CarSettings mergedSettings = currentSettings.merge(settings);

    String settingsJsonString = _settingsSerializer->serializeCarSettings(mergedSettings);

    _logger->println("Saving settings: " + settingsJsonString);

    _fileSystem->writeContent(SETTINGS_PATH, settingsJsonString);

    _stateOwner->setCarSettings(mergedSettings);
}