#include "Includes.h"

WiFiRcHost::WiFiRcHost(
    Logger *logger,
    FileSystem *fileSystem,
    SerialTransmitter *serialTransmitter)
{
    _logger = logger;
    _fileSystem = fileSystem;
    _serialTransmitter = serialTransmitter;
}

void WiFiRcHost::loop()
{
    _server.handleClient();
}

bool WiFiRcHost::setup()
{
    _server.begin();

    _server.on("/", HTTP_GET, std::bind(&WiFiRcHost::handleRoot, this));
    _server.on("/images/background.jpg", std::bind(&WiFiRcHost::handleBackgroundImage, this));
    _server.on("/images/gas.png", std::bind(&WiFiRcHost::handleGasImage, this));
    _server.on("/images/wheel.png", std::bind(&WiFiRcHost::handleWheelImage, this));
    _server.on("/app.js", HTTP_GET, std::bind(&WiFiRcHost::handleAppScript, this));
    _server.on("/api/state", HTTP_POST, std::bind(&WiFiRcHost::handleState, this));

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

void WiFiRcHost::handleState()
{

    String gasString = _server.arg("gas");
    float gas = gasString.toFloat();

    String wheelString = _server.arg("wheel");
    float wheel = wheelString.toFloat();

    CarState state;
    state.gas = gas;
    state.wheel = wheel;

    _serialTransmitter->transmitState(&state);

    _server.send(200);

    _logger->println("State handled.");
    _logger->print("gas: ");
    _logger->println(gas);
    _logger->print("wheel: ");
    _logger->println(wheel);
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