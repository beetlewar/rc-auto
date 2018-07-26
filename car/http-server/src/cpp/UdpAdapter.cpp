#include "Includes.h"

UdpAdapter::UdpAdapter(Logger *logger, StateOwner *stateOwner)
{
    _logger = logger;
    _stateOwner = stateOwner;
}

bool UdpAdapter::setup()
{
    _udp.begin(UDP_PORT);

    _logger->println("Udp server started at port: " + String(UDP_PORT) + ", real port: " + String(_udp.localPort()));

    return true;
}

void UdpAdapter::loop()
{
    int packetSize = _udp.parsePacket();
    int avail = _udp.available();
    if (avail > 0)
    {
        _logger->println(avail);
    }
    if (packetSize == 0)
    {
        return;
    }

    _logger->println("Received: " + String(packetSize) + " via udp");

    int expectedPacketSize = sizeof(RemoteCarState);
    if (packetSize != expectedPacketSize)
    {
        _logger->println("Unexpected packet size " + String(packetSize));
        return;
    }

    uint8_t buffer[expectedPacketSize];
    _udp.readBytes(buffer, expectedPacketSize);

    RemoteCarState remoteCarState = _serializer.deserialize(buffer);
    _logger->println(String(remoteCarState.Gas) + ", " + String(remoteCarState.Wheel));

    _stateOwner->setCarState(CarState(remoteCarState, millis()));
}