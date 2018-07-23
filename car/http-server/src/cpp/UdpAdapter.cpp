#include "Includes.h"

UdpAdapter::UdpAdapter(Logger *logger, StateOwner *stateOwner)
{
    _logger = logger;
    _stateOwner = stateOwner;
}

bool UdpAdapter::setup()
{
    _udp.begin(UDP_PORT);

    _logger->println("Udp server started at port " + String(UDP_PORT));

    return true;
}

void UdpAdapter::loop()
{
    int packetSize = _udp.parsePacket();
    if (packetSize == 0)
    {
        return;
    }

    int expectedPacketSize = sizeof(RemoteCarState);
    if (packetSize != expectedPacketSize)
    {
        _logger->println("Unexpected packet size " + String(packetSize));
        return;
    }

    uint8_t buffer[expectedPacketSize];
    _udp.readBytes(buffer, expectedPacketSize);

    RemoteCarState remoteCarState = _serializer.deserialize(buffer);

    _stateOwner->setCarState(CarState(remoteCarState, millis()));
}