#pragma once

#include "..\..\Includes.h"

class CarMessageHandler : public AbstractCarMessageHandler
{
  private:
    Car *_car;

  public:
    CarMessageHandler(Car *car);
    virtual void publishWheelRotation(float value);
    virtual void publishGas(float value);
};