#include "Includes.h"

bool Logger::setup(int serialSpeed)
{
    Serial.begin(serialSpeed);

    println("");
    println("------STARTING NEW APPLICATION-------");

    return true;
}

void Logger::print(String s)
{
    Serial.print(s);
}

void Logger::print(long l)
{
    Serial.print(l);
}

void Logger::print(int i)
{
    Serial.print(i);
}

void Logger::print(float f)
{
    Serial.print(f);
}

void Logger::println(String s)
{
    Serial.println(s);
}

void Logger::println(long l)
{
    Serial.println(l);
}

void Logger::println(int i)
{
    Serial.println(i);
}

void Logger::println(float f)
{
    Serial.println(f);
}