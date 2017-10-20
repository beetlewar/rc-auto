#pragma once

#include "..\..\Includes.h"

class AbstractCarMessageHandler
{
  public:
    virtual void publishWheelRotation(float value) = 0;
    virtual void publishGas(float value) = 0;
};