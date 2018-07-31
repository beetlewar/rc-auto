#include "Includes.h"

const int STATE_BUF_SIZE = 200;
const int SETTINGS_BUF_SIZE = 200;

CarSettingsJsonSerializer::CarSettingsJsonSerializer(Logger *logger)
{
    _logger = logger;
}

RemoteCarState CarSettingsJsonSerializer::deserializeRemoteCarState(String str)
{
    StaticJsonBuffer<STATE_BUF_SIZE> jsonBuffer;

    String upperStr = str;
    upperStr.toUpperCase();

    JsonObject &root = jsonBuffer.parseObject(upperStr);

    if (!root.success())
    {
        Serial.println("Failed to parse car state");
        return RemoteCarState();
    }

    float gas = parseFloat(&root, "GAS", 0);
    float wheel = parseFloat(&root, "WHEEL", 0);

    return RemoteCarState(gas, wheel);
}

CarSettings CarSettingsJsonSerializer::deserializeCarSettings(String str)
{
    StaticJsonBuffer<SETTINGS_BUF_SIZE> jsonBuffer;

    String upperStr = str;
    upperStr.toUpperCase();

    JsonObject &root = jsonBuffer.parseObject(upperStr);

    if (!root.success())
    {
        Serial.println("Failed to parse car settings");
        return CarSettings();
    }

    float engineForwardPower = parseFloat(&root, "ENGINEFORWARDPOWER", UNSPECIFIED_SETTINGS_FLOAT_VALUE);
    float engineBackwardPower = parseFloat(&root, "ENGINEBACKWARDPOWER", UNSPECIFIED_SETTINGS_FLOAT_VALUE);
    float engineAcceleration = parseFloat(&root, "ENGINEACCELERATION", UNSPECIFIED_SETTINGS_FLOAT_VALUE);

    return CarSettings(engineForwardPower, engineBackwardPower, engineAcceleration);
}

String CarSettingsJsonSerializer::serializeCarSettings(CarSettings settings)
{
    StaticJsonBuffer<SETTINGS_BUF_SIZE> jsonBuffer;

    JsonObject &root = jsonBuffer.createObject();

    if (settings.EngineForwardPower() != UNSPECIFIED_SETTINGS_FLOAT_VALUE)
    {
        root["engineForwardPower"] = settings.EngineForwardPower();
    }

    if (settings.EngineBackwardPower() != UNSPECIFIED_SETTINGS_FLOAT_VALUE)
    {
        root["engineBackwardPower"] = settings.EngineBackwardPower();
    }

    if (settings.EngineAcceleration() != UNSPECIFIED_SETTINGS_FLOAT_VALUE)
    {
        root["engineAcceleration"] = settings.EngineAcceleration();
    }

    String result;
    root.printTo(result);

    return result;
}

float CarSettingsJsonSerializer::parseFloat(JsonObject *obj, String name, float defaultValue)
{
    if (!obj->containsKey(name))
    {
        return defaultValue;
    }

    float value = (*obj)[name].as<float>();

    if (value == defaultValue)
    {
        return defaultValue;
    }

    if (value < -1)
    {
        return -1;
    }
    if (value > 1)
    {
        return 1;
    }

    return value;
}