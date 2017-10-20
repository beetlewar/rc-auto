#include <Arduino.h>
#include <unity.h>

#ifdef UNIT_TEST

void do_some_test()
{
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
}

void loop()
{
    RUN_TEST(do_some_test);

    UNITY_END();
}

#endif