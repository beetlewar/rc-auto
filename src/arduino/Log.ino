// #define DEBUG

bool setupLog()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif
    return true;
}

void printLog(String s)
{
#ifdef DEBUG
    Serial.print(s);
#endif
}

void printlnLog(String s)
{
#ifdef DEBUG
    Serial.println(s);
#endif
}

void printlnLog(float f)
{
#ifdef DEBUG
    Serial.println(f);
#endif
}