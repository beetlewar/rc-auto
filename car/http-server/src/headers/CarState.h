#pragma once

class CarState
{
  private:
    float _gas;
    float _wheel;
    unsigned long _keepAliveTime;

  public:
    CarState(float gas, float wheel, unsigned long keepAliveTime)
    {
        _gas = gas;
        _wheel = wheel;
        _keepAliveTime = keepAliveTime;
    }

    CarState(const CarState &state)
    {
        _gas = state._gas;
        _wheel = state._wheel;
        _keepAliveTime = state._keepAliveTime;
    }

    float gas()
    {
        return _gas;
    }

    float wheel()
    {
        return _wheel;
    }

    unsigned long keepAliveTime()
    {
        return _keepAliveTime;
    }
};