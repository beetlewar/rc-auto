#include "Includes.h"

HttpAdapter::HttpAdapter(
    Logger *logger,
    FileSystem *fileSystem,
    StateOwner *stateOwner)
{
    _logger = logger;
    _fileSystem = fileSystem;
    _stateOwner = stateOwner;
}

void HttpAdapter::loop()
{
    _server.handleClient();
}

bool HttpAdapter::setup()
{
    _server.begin();

    _server.on("/", HTTP_GET, std::bind(&HttpAdapter::handleRoot, this));
    _server.on("/images/background.jpg", std::bind(&HttpAdapter::handleBackgroundImage, this));
    _server.on("/images/gas.png", std::bind(&HttpAdapter::handleGasImage, this));
    _server.on("/images/wheel.png", std::bind(&HttpAdapter::handleWheelImage, this));
    _server.on("/app.js", HTTP_GET, std::bind(&HttpAdapter::handleAppScript, this));
    _server.on("/api/state", HTTP_POST, std::bind(&HttpAdapter::handleState, this));

    _logger->println("Http server started at port 80.");

    return true;
}

void HttpAdapter::handleRoot()
{
    _logger->println("Handling Index.html.");

    String content = readFileAsString("/Index.html");

    _server.send(200, "text/html", content);
}

void HttpAdapter::handleBackgroundImage()
{
    sendFile("/images/background.jpg", "image/jpeg");
}

void HttpAdapter::handleGasImage()
{
    sendFile("/images/gas.png", "image/png");
}

void HttpAdapter::handleWheelImage()
{
    sendFile("/images/wheel.png", "image/png");
}

void HttpAdapter::handleAppScript()
{
    _logger->println("Handling app script.");

    String content = readFileAsString("/app.js");

    _server.send(200, "application/javascript", content);
}

void HttpAdapter::handleState()
{
    String gasString = _server.arg("gas");
    float gas = gasString.toFloat();

    String wheelString = _server.arg("wheel");
    float wheel = wheelString.toFloat();

    CarState state(RemoteCarState(gas, wheel), millis());

    _stateOwner->setCarState(state);

    _logger->println("State handled.");
    _logger->println("gas: " + String(gas) + ", wheel: " + String(wheel) + ", at: " + String(state.KeepAliveTime));

    _server.send(200);
}

void HttpAdapter::sendFile(String path, String contentType)
{
    _logger->print("Handling file ");
    _logger->println(path);

    File file = _fileSystem->openRead(path);

    _server.streamFile(file, contentType);

    file.close();
}

String HttpAdapter::readFileAsString(String path)
{
    File file = _fileSystem->openRead(path);

    String result = file.readStringUntil('\0');

    file.close();

    return result;
}