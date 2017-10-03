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

    Serial.print("Setting gas to ");
    Serial.println(gasValue);

    analogWrite(gasPin, gasValue);
}

void setCarRotation(float value)
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

    Serial.print("Setting left rotation to ");
    Serial.println(leftValue);

    analogWrite(leftPin, leftValue);

    Serial.print("Setting right rotation to ");
    Serial.println(rightValue);

    analogWrite(rightPin, rightValue);
}