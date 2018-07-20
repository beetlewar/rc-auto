#pragma once

struct RemoteCarState
{
    float Gas;
    float Wheel;

  public:
    RemoteCarState(float gas, float wheel)
    {
        Gas = gas;
        Wheel = wheel;
    }
};

class RemoteCarStateSerializer
{
  public:
    unsigned long serialize(RemoteCarState carState, uint8_t *destination)
    {
        binaryFloat gas;
        gas.value = carState.Gas;

        memcpy(destination, gas.binary, sizeof(gas));
        destination += sizeof(gas);

        binaryFloat wheel;
        wheel.value = carState.Wheel;

        memcpy(destination, wheel.binary, sizeof(wheel));
        destination += sizeof(wheel);

        return sizeof(RemoteCarState);
    }

    RemoteCarState deserialize(uint8_t *bytes)
    {
        binaryFloat gas;
        memcpy(gas.binary, bytes, sizeof(gas));
        bytes += sizeof(gas);

        binaryFloat wheel;
        memcpy(wheel.binary, bytes, sizeof(wheel));
        bytes += sizeof(wheel);

        return RemoteCarState(gas.value, wheel.value);
    }
};