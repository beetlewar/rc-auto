#pragma once

#include "Includes.h"

class Logger
{
  public:
    bool setup(int serialSpeed)
    {
#ifdef DEBUG

        Serial.begin(serialSpeed);

        println("");
        println("------STARTING NEW APPLICATION-------");

#endif

        return true;
    }

    void print(String s)
    {
#ifdef DEBUG

        Serial.print(s);

#endif
    }

    void print(long l)
    {
#ifdef DEBUG

        Serial.print(l);

#endif
    }

    void print(int i)
    {
#ifdef DEBUG

        Serial.print(i);

#endif
    }

    void print(float f)
    {
#ifdef DEBUG

        Serial.print(f);

#endif
    }

    void println(String s)
    {
#ifdef DEBUG

        Serial.println(s);

#endif
    }

    void println(long l)
    {
#ifdef DEBUG

        Serial.println(l);

#endif
    }

    void println(int i)
    {
#ifdef DEBUG

        Serial.println(i);

#endif
    }

    void println(float f)
    {
#ifdef DEBUG

        Serial.println(f);

#endif
    }
};