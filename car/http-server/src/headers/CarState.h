#pragma once

struct CarState
{
    RemoteCarState State;
    unsigned long KeepAliveTime;

    CarState(RemoteCarState state, unsigned long keepAliveTime)
    {
        State = state;
        KeepAliveTime = keepAliveTime;
    }

    CarState(const CarState &state)
    {
        State = state.State;
        KeepAliveTime = state.KeepAliveTime;
    }
};