#pragma once

class SerialSerializer
{
  public:
    unsigned long serialize(const CarStateMessage *message, uint8_t *destination)
    {
        destination = writeULong(message->ServerTime, destination);
        destination = writeULong(message->KeepAliveTime, destination);
        destination = writeFloat(message->Gas, destination);
        destination = writeFloat(message->Wheel, destination);
        destination = writeFloat(message->EngineForwardPower, destination);
        destination = writeFloat(message->EngineBackwardPower, destination);
        destination = writeFloat(message->AccelerationPower, destination);

        return sizeof(CarStateMessage);
    }

    uint8_t *writeULong(unsigned long value, uint8_t *destination)
    {
        binaryULong bul;
        bul.value = value;
        memcpy(destination, bul.binary, sizeof(bul));
        return destination + sizeof(bul);
    }

    uint8_t *writeFloat(float value, uint8_t *destination)
    {
        binaryFloat bf;
        bf.value = value;
        memcpy(destination, bf.binary, sizeof(bf));
        return destination + sizeof(bf);
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

        binaryFloat engineForward;
        memcpy(engineForward.binary, bytes, sizeof(engineForward));
        bytes += sizeof(engineForward);

        binaryFloat engineBackward;
        memcpy(engineBackward.binary, bytes, sizeof(engineBackward));
        bytes += sizeof(engineBackward);

        binaryFloat acceleration;
        memcpy(acceleration.binary, bytes, sizeof(acceleration));
        bytes += sizeof(acceleration);

        return CarStateMessage(
            serverTime.value,
            keepAliveTime.value,
            gas.value,
            wheel.value,
            engineForward.value,
            engineBackward.value,
            acceleration.value);
    }
};
