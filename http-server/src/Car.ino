const int leftPin = D9;
const int rightPin = D10;
const int gasPin = D11;

bool setupCar()
{
    pinMode(leftPin, OUTPUT);
    pinMode(rightPin, OUTPUT);
    pinMode(gasPin, OUTPUT);

    return true;
}

void setCarGas(float value)
{
    int gasValue = (int)(255 * value);

    printLog("Setting gas to ");
    printlnLog(gasValue);

    analogWrite(gasPin, gasValue);
}

void setCarWheel(float value)
{
    int leftValue = 0;
    int rightValue = 0;

    if (value < 0)
    {
        leftValue = (int)(-255 * value);
    }
    else if (value > 0)
    {
        rightValue = (int)(255 * value);
    }

    printLog("Setting left wheel to ");
    printlnLog(leftValue);

    analogWrite(leftPin, leftValue);

    printLog("Setting right wheel to ");
    printlnLog(rightValue);

    analogWrite(rightPin, rightValue);
}