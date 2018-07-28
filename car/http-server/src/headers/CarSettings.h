#pragma once

const float UNSPECIFIED_SETTINGS_FLOAT_VALUE = -9999999;

class CarSettings
{
  private:
    float _engineForwardPower;
    float _engineBackwardPower;
    float _engineAcceleration;

  public:
    CarSettings()
    {
        _engineForwardPower = _engineBackwardPower = _engineAcceleration = UNSPECIFIED_SETTINGS_FLOAT_VALUE;
    }

    CarSettings(float engineForwardPower, float engineBackwardPower, float engineAcceleration)
    {
        _engineForwardPower = normalize(engineForwardPower);
        _engineBackwardPower = normalize(engineBackwardPower);
        _engineAcceleration = normalize(engineAcceleration);
    }

    CarSettings(const CarSettings &settings)
    {
        _engineForwardPower = settings._engineForwardPower;
        _engineBackwardPower = settings._engineBackwardPower;
        _engineAcceleration = settings._engineAcceleration;
    }

    float EngineForwardPower() { return _engineForwardPower; }
    float EngineBackwardPower() { return _engineBackwardPower; }
    float EngineAcceleration() { return _engineAcceleration; }

  private:
    float normalize(float value)
    {
        if (value == UNSPECIFIED_SETTINGS_FLOAT_VALUE)
        {
            return value;
        }

        if (value > 1)
        {
            return 1;
        }

        if (value < -1)
        {
            return -1;
        }

        return value;
    }
};