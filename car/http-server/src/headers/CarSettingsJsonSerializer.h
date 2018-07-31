#pragma once

class CarSettingsJsonSerializer
{
private:
  Logger *_logger;

public:
  CarSettingsJsonSerializer(Logger *logger);

  RemoteCarState deserializeRemoteCarState(String str);

  CarSettings deserializeCarSettings(String str);

  String serializeCarSettings(CarSettings settings);

private:
  float parseFloat(JsonObject *obj, String name, float defaultValue);
};