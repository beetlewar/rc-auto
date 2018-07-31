#pragma once

#include "Includes.h"

class StateOwner
{
  private:
    CarState _carState;
    CarSettings _carSettings;
    Logger *_logger;

  public:
    StateOwner(Logger *logger) : _carState(RemoteCarState(0, 0), 0),
                                 _carSettings(ENGINE_FORWARD_POWER, ENGINE_BACKWARD_POWER, ENGINE_ACCELERATION_POWER)
    {
        _logger = logger;
    }

    void setCarState(CarState state)
    {
        _carState = state;
    }

    void setCarSettings(CarSettings settings)
    {
        _carSettings = settings;

        _logger->println("Settings changed");
        _logger->println("F: " + String(settings.EngineForwardPower()) +
                         ", B: " + String(settings.EngineBackwardPower()) +
                         ", A: " + String(settings.EngineAcceleration()));
    }

    CarState getCarState()
    {
        return _carState;
    }

    CarSettings getCarSettings()
    {
        return _carSettings;
    }
};