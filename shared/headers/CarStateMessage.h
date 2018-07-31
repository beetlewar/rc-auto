#pragma once

struct CarStateMessage
{
    unsigned long ServerTime;
    unsigned long KeepAliveTime;
    float Gas;
    float Wheel;
    float EngineForwardPower;
    float EngineBackwardPower;
    float AccelerationPower;

    CarStateMessage(
        unsigned long serverTime,
        unsigned long keepAliveTime,
        float gas,
        float wheel,
        float engineForwardPower,
        float engineBackwardPower,
        float accelerationPower)
    {
        ServerTime = serverTime;
        KeepAliveTime = keepAliveTime;
        Gas = gas;
        Wheel = wheel;
        EngineForwardPower = engineForwardPower;
        EngineBackwardPower = engineBackwardPower;
        AccelerationPower = accelerationPower;
    }
};