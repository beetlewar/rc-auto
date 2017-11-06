#pragma once

class I2CMaster{
private:
    Logger *_logger;
public:
    I2CMaster(Logger *logger);
    bool setup();
    void publishGas(float value);
    void publishWheelRotation(float value);
};