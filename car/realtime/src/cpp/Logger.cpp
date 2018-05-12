#include "Includes.h"

//#define DEBUG

bool Logger::setup(int serialSpeed)
{
#ifdef DEBUG

    Serial.begin(serialSpeed);

    println("");
    println("------STARTING NEW CAR APPLICATION-------");

#endif

    return true;
}

void Logger::print(String s)
{
#ifdef DEBUG

    Serial.print(s);

#endif
}

void Logger::print(long l)
{
#ifdef DEBUG

    Serial.print(l);

#endif
}

void Logger::print(int i)
{
#ifdef DEBUG

    Serial.print(i);

#endif
}

void Logger::print(float f)
{
#ifdef DEBUG

    Serial.print(f);

#endif
}

void Logger::println(String s)
{
#ifdef DEBUG

    Serial.println(s);

#endif
}

void Logger::println(long l)
{
#ifdef DEBUG

    Serial.println(l);

#endif
}

void Logger::println(int i)
{
#ifdef DEBUG

    Serial.println(i);

#endif
}

void Logger::println(float f)
{
#ifdef DEBUG

    Serial.println(f);

#endif
}