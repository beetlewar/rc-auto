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

    // html
    _server.on("/", HTTP_GET, std::bind(&HttpAdapter::handleRoot, this));
    _server.on("/admin", std::bind(&HttpAdapter::handleAdminPage, this));

    // api
    _server.on("/api/state", HTTP_POST, std::bind(&HttpAdapter::handleState, this));

    // static
    _server.on("/app.js", HTTP_GET, std::bind(&HttpAdapter::handleAppScript, this));
    _server.on("/images/background.jpg", std::bind(&HttpAdapter::handleBackgroundImage, this));
    _server.on("/images/gas.png", std::bind(&HttpAdapter::handleGasImage, this));
    _server.on("/images/wheel.png", std::bind(&HttpAdapter::handleWheelImage, this));
    _server.on("/bootstrap/bootstrap.min.css", std::bind(&HttpAdapter::handleBootstrapMinCss, this));
    _server.on("/bootstrap/bootstrap.min.js", std::bind(&HttpAdapter::handleBootstrapMinJs, this));
    _server.on("/bootstrap/jquery-3.3.1.min.js", std::bind(&HttpAdapter::handleJQuery, this));
    _server.on("/bootstrap/popper.min.js", std::bind(&HttpAdapter::handlePopper, this));
    _server.on("/custom_styles/slider.css", std::bind(&HttpAdapter::handleSliderCss, this));

    _logger->println("Http server started at port 80.");

    return true;
}

void HttpAdapter::handleRoot()
{
    sendFile("/Index.html", "text/html");
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
    sendFile("/app.js", "application/javascript");
}

void HttpAdapter::handleAdminPage()
{
    sendFile("/Admin.html", "text/html");
}

void HttpAdapter::handleBootstrapMinCss()
{
    sendFile("/bootstrap/bootstrap.min.css", "text/css");
}

void HttpAdapter::handleBootstrapMinJs()
{
    sendFile("/bootstrap/bootstrap.min.js", "application/javascript");
}

void HttpAdapter::handleJQuery()
{
    sendFile("/bootstrap/jquery-3.3.1.min.js", "application/javascript");
}

void HttpAdapter::handlePopper()
{
    sendFile("/bootstrap/popper.min.js", "application/javascript");
}

void HttpAdapter::handleSliderCss()
{
    sendFile("/custom_styles/slider.css", "text/css");
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