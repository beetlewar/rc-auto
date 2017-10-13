#include "Includes.h"

const byte DNS_PORT = 53;
const String DNS = "www.rc-host.ru";

WiFiRcHost::WiFiRcHost(Logger *logger, FileSystem *fileSystem, Car *car)
{
    _logger = logger;
    _fileSystem = fileSystem;
    _car = car;
}

void WiFiRcHost::loop()
{
    _dnsServer.processNextRequest();
    _server.handleClient();
}

bool WiFiRcHost::setup()
{
    _dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    _dnsServer.start(DNS_PORT, DNS, IPAddress(192, 168, 4, 1));

    _logger->print("DNS: ");
    _logger->println(DNS);

    _server.begin();

    _server.on("/", HTTP_GET, std::bind(&WiFiRcHost::handleRoot, this));
    _server.on("/images/background.jpg", std::bind(&WiFiRcHost::handleBackgroundImage, this));
    _server.on("/images/gas.png", std::bind(&WiFiRcHost::handleGasImage, this));
    _server.on("/images/wheel.png", std::bind(&WiFiRcHost::handleWheelImage, this));
    _server.on("/app.js", HTTP_GET, std::bind(&WiFiRcHost::handleAppScript, this));
    _server.on("/api/gas", HTTP_PUT, std::bind(&WiFiRcHost::handleGas, this));
    _server.on("/api/wheel", HTTP_PUT, std::bind(&WiFiRcHost::handleWheel, this));

    _logger->println("Http server started at port 80.");

    return true;
}

void WiFiRcHost::handleRoot()
{
    _logger->println("Handling Index.html.");

    String content = readFileAsString("/Index.html");

    _server.send(200, "text/html", content);
}

void WiFiRcHost::handleBackgroundImage()
{
    sendFile("/images/background.jpg", "image/jpeg");
}

void WiFiRcHost::handleGasImage()
{
    sendFile("/images/gas.png", "image/png");
}

void WiFiRcHost::handleWheelImage()
{
    sendFile("/images/wheel.png", "image/png");
}

void WiFiRcHost::handleAppScript()
{
    _logger->println("Handling app script.");

    String content = readFileAsString("/app.js");

    _server.send(200, "application/javascript", content);
}

void WiFiRcHost::handleGas()
{
    _logger->println("Handling API gas.");

    String gasString = _server.arg("gas");
    float gas = gasString.toFloat();
    _logger->print("gas: ");
    _logger->println(gas);

    _car->setGas(gas);

    _server.send(200);
}

void WiFiRcHost::handleWheel()
{
    _logger->println("Handling API wheel.");

    String wheelString = _server.arg("wheel");
    float wheel = wheelString.toFloat();
    _logger->print("wheel: ");
    _logger->println(wheel);

    _car->setWheel(wheel);

    _server.send(200);
}

void WiFiRcHost::sendFile(String path, String contentType)
{
    _logger->print("Handling file ");
    _logger->println(path);

    File file = _fileSystem->openRead(path);

    _server.streamFile(file, contentType);

    file.close();
}

String WiFiRcHost::readFileAsString(String path)
{
    File file = _fileSystem->openRead(path);

    String result = file.readStringUntil('\0');

    file.close();

    return result;
}