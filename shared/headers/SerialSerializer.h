#pragma once

class SerialSerializer
{
  public:
    unsigned long serialize(const CarStateMessage *message, uint8_t *destination)
    {
        binaryULong unionServerTime;
        unionServerTime.value = message->ServerTime;

        memcpy(destination, unionServerTime.binary, sizeof(unionServerTime));
        destination += sizeof(unionServerTime);

        binaryULong keepAliveTime;
        keepAliveTime.value = message->KeepAliveTime;

        memcpy(destination, keepAliveTime.binary, sizeof(keepAliveTime));
        destination += sizeof(keepAliveTime);

        binaryFloat gas;
        gas.value = message->Gas;

        memcpy(destination, gas.binary, sizeof(gas));
        destination += sizeof(gas);

        binaryFloat wheel;
        wheel.value = message->Wheel;

        memcpy(destination, wheel.binary, sizeof(wheel));
        destination += sizeof(wheel);

        return sizeof(CarStateMessage);
    }

    CarStateMessage deserialize(uint8_t *bytes)
    {
        binaryULong serverTime;
        memcpy(serverTime.binary, bytes, sizeof(serverTime));
        bytes += sizeof(serverTime);

        binaryULong keepAliveTime;
        memcpy(keepAliveTime.binary, bytes, sizeof(keepAliveTime));
        bytes += sizeof(keepAliveTime);

        binaryFloat gas;
        memcpy(gas.binary, bytes, sizeof(gas));
        bytes += sizeof(gas);

        binaryFloat wheel;
        memcpy(wheel.binary, bytes, sizeof(wheel));
        bytes += sizeof(wheel);

        return CarStateMessage(
            serverTime.value,
            keepAliveTime.value,
            gas.value,
            wheel.value);
    }
};
