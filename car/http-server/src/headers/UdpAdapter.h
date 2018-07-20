#pragma once

class UdpAdapter
{
  private:
    WiFiUDP _udp;
    Logger *_logger;
    StateOwner *_stateOwner;
    RemoteCarStateSerializer _serializer;

  public:
    UdpAdapter(Logger *logger, StateOwner *stateOwner);
    bool setup();
    void loop();
};