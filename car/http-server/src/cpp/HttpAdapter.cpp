#include "Includes.h"

HttpAdapter::HttpAdapter(
    Logger *logger,
    FileSystem *fileSystem,
    StateOwner *stateOwner,
    CarSettingsJsonSerializer *settingsSerializer)
{
    _logger = logger;
    _fileSystem = fileSystem;
    _stateOwner = stateOwner;
    _settingsSerializer = settingsSerializer;
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
    _server.on("/api/state", HTTP_POST, std::bind(&HttpAdapter::handlePostState, this));
    _server.on("/api/settings", HTTP_GET, std::bind(&HttpAdapter::handleGetSettings, this));
    _server.on("/api/settings", HTTP_POST, std::bind(&HttpAdapter::handlePostSettings, this));
    _server.on("/api/settings/reset", HTTP_POST, std::bind(&HttpAdapter::handlePostSettingsReset, this));

    // static
    _server.on("/app.js", HTTP_GET, std::bind(&HttpAdapter::handleAppScript, this));
    _server.on("/images/background.jpg", std::bind(&HttpAdapter::handleBackgroundImage, this));
    _server.on("/images/gas.png", std::bind(&HttpAdapter::handleGasImage, this));
    _server.on("/images/wheel.png", std::bind(&HttpAdapter::handleWheelImage, this));
    _server.on("/externaljs/jquery-3.3.1.min.js", std::bind(&HttpAdapter::handleJQuery, this));
    _server.on("/styles/custom.css", std::bind(&HttpAdapter::handleCustomStyles, this));

    _logger->println("Http server started at port 80");

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

void HttpAdapter::handleJQuery()
{
    sendFile("/externaljs/jquery-3.3.1.min.js", "application/javascript");
}

void HttpAdapter::handleCustomStyles()
{
    sendFile("/styles/custom.css", "text/css");
}

void HttpAdapter::handleGetSettings()
{
    _logger->println("Get settings handled.");

    const String settingsJson =
        "{ " + String("\"engineForwardPower\": \"0.33\"") + " }";

    _server.send(200, "application/json", settingsJson);
}

void HttpAdapter::handlePostState()
{
    if (!_server.hasArg("plain"))
    {
        _logger->println("No car state body received");
        _server.send(400);
        return;
    };

    String body = _server.arg("plain");
    _logger->println(body);

    RemoteCarState remoteCarState = _settingsSerializer->deserializeRemoteCarState(body);
    _logger->println(String(remoteCarState.Gas) + ", " + String(remoteCarState.Wheel));

    CarState state(remoteCarState, millis());
    _stateOwner->setCarState(state);

    _logger->println("State handled.");
    _server.send(200);
}

void HttpAdapter::handlePostSettings()
{
    if (!_server.hasArg("plain"))
    {
        _logger->println("No settings body received");
        _server.send(400);
        return;
    };

    String body = _server.arg("plain");
    _logger->println(body);

    CarSettings settings = _settingsSerializer->deserializeCarSettings(body);
    _logger->println(String(settings.EngineForwardPower()) +
                     ", " + String(settings.EngineBackwardPower()) +
                     ", " + String(settings.EngineAcceleration()));

    _logger->println("Post settings handled.");
    _server.send(200);
}

void HttpAdapter::handlePostSettingsReset()
{
    _logger->println("Post reset settings handled.");
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