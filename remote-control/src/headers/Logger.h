#pragma once

#include "../Includes.h"

class Logger{
public:
    bool setup(int serialSpeed);

    void print(String s);

    void print(long l);

    void print(int i);

    void print(float f);

    void println(String s);

    void println(long l);

    void println(int i);

    void println(float f);
};