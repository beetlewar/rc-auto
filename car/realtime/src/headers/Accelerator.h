#pragma once

class Accelerator
{
  private:
    double _acceleratedValue;
    uint64_t _accelerationTime;
    Logger *_logger;

  public:
    Accelerator(Logger *logger);
    float accelerate(float targetValue, float accelerationPower);

  private:
    double animateAcceleration(
        double currentAcceleration,
        float targetValue,
        float accelerationPower,
        uint64_t time,
        uint64_t lastTime);
    double normalizeAcceleration(float targetValue, double acceleratedValue);
};