#include "Includes.h"

HttpAdapter::HttpAdapter(
    Logger *logger,
    FileSystem *fileSystem,
    StateOwner *stateOwner,
    CarSettingsJsonSerializer *settingsSerializer,
    CarSettingsRepository *settingsRepository)
{
    _logger = logger;
    _fileSystem = fileSystem;
    _stateOwner = stateOwner;
    _settingsSerializer = settingsSerializer;
    _settingsRepository = settingsRepository;
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

void HttpAdapter::handlePostState()
{
    _logger->println("Handling POST state.");

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

    _server.send(200);

    _logger->println("POST state handled.");
}

void HttpAdapter::handleGetSettings()
{
    _logger->println("Handling GET settings.");

    CarSettings settings = _settingsRepository->getSettings();
    String settingsJson = _settingsSerializer->serializeCarSettings(settings);

    _server.send(200, "application/json", settingsJson);

    _logger->println("GET settings handled.");
}

void HttpAdapter::handlePostSettings()
{
    _logger->println("Handling POST settings.");

    if (!_server.hasArg("plain"))
    {
        _logger->println("No settings body received");
        _server.send(400);
        return;
    };

    String body = _server.arg("plain");

    CarSettings settings = _settingsSerializer->deserializeCarSettings(body);

    _settingsRepository->saveSettings(settings);

    _server.send(200);

    _logger->println("POST settings handled.");
}

void HttpAdapter::handlePostSettingsReset()
{
    _logger->println("Handling POST reset settings.");

    CarSettings defaultSettings = CarSettings(
        ENGINE_FORWARD_POWER,
        ENGINE_BACKWARD_POWER,
        ENGINE_ACCELERATION_POWER);

    _settingsRepository->saveSettings(defaultSettings);

    CarSettings settings = _settingsRepository->getSettings();
    String settingsJson = _settingsSerializer->serializeCarSettings(settings);

    _server.send(200, "application/json", settingsJson);

    _logger->println("POST reset settings handled.");
}

void HttpAdapter::sendFile(String path, String contentType)
{
    _logger->print("Handling file ");
    _logger->println(path);

    File file = _fileSystem->openRead(path);

    _server.streamFile(file, contentType);

    file.close();
}