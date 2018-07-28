#include "Includes.h"

CarSettingsJsonSerializer::CarSettingsJsonSerializer(Logger *logger)
{
    _logger = logger;
}

RemoteCarState CarSettingsJsonSerializer::deserializeRemoteCarState(String str)
{
    StaticJsonBuffer<200> jsonBuffer;

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
    StaticJsonBuffer<200> jsonBuffer;

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

float CarSettingsJsonSerializer::parseFloat(JsonObject *obj, String name, float defaultValue)
{
    if (!obj->containsKey(name))
    {
        return defaultValue;
    }

    float value = (*obj)[name].as<float>();

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