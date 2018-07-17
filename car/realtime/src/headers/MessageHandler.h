#pragma once

class MessageHandler
{
  private:
    Logger *_logger;
    SerialSerializer *_serializer;
    Car *_car;

  public:
    MessageHandler(
        Logger *logger,
        SerialSerializer *serializer,
        Car *car);

    void handle(uint8_t *message);
};