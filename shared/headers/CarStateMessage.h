#pragma once

struct CarStateMessage
{
    unsigned long ServerTime;
    unsigned long KeepAliveTime;
    float Gas;
    float Wheel;

    CarStateMessage(
        unsigned long serverTime,
        unsigned long keepAliveTime,
        float gas,
        float wheel)
    {
        ServerTime = serverTime;
        KeepAliveTime = keepAliveTime;
        Gas = gas;
        Wheel = wheel;
    }
};