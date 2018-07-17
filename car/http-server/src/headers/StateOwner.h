#pragma once

#include "Includes.h"

class StateOwner
{
  private:
    CarState _carState;

  public:
    StateOwner() : _carState(0, 0, 0)
    {
    }

    void setCarState(CarState state)
    {
        _carState = state;
    }

    CarState getCarState()
    {
        return _carState;
    }
};