#pragma once

struct RemoteCarState
{
    float Gas;
    float Wheel;

    RemoteCarState() : Gas(0), Wheel(0)
    {
    }

    RemoteCarState(float gas, float wheel)
    {
        Gas = gas;
        Wheel = wheel;
    }

    RemoteCarState(const RemoteCarState &another)
    {
        Gas = another.Gas;
        Wheel = another.Wheel;
    }

  private:
    bool FloatMeasuresEqual(float f1, float f2)
    {
        float delta = f2 - f1;
        if (delta < 0)
        {
            delta = -delta;
        }

        return delta <= 0.1f;
    }

  public:
    bool StateChanged(const RemoteCarState *another)
    {
        return !FloatMeasuresEqual(Gas, another->Gas) || !FloatMeasuresEqual(Wheel, another->Wheel);
    }
};