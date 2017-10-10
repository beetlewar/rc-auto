#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

bool setupRcHost()
{
    server.begin();

    server.on("/", HTTP_GET, handleRoot);
    server.on("/images/background.jpg", handleBackgroundImage);
    server.on("/images/gas.png", handleGasImage);
    server.on("/images/wheel.png", handleWheelImage);
    server.on("/js/window.js", HTTP_GET, handleWindowScript);
    server.on("/js/gas.js", HTTP_GET, handleGasScript);
    server.on("/js/wheel.js", HTTP_GET, handleWheelScript);
    server.on("/api/gas", HTTP_PUT, handleGas);
    server.on("/api/wheel", HTTP_PUT, handleWheel);

    printlnLog("Http server started at port 80.");

    return true;
}

void loopRcHost()
{
    server.handleClient();
}

void handleNotFound()
{
    printlnLog("Handling not found.");

    server.send(404, "text/plain", "Not found");
}

void handleRoot()
{
    printlnLog("Handling index.hml.");

    String content = readFileString("/Index.html");

    server.send(200, "text/html", content);
}

void sendFile(String path, String contentType)
{
    printLog("Handling file ");
    printlnLog(path);

    File file = SPIFFS.open(path, "r");

    server.streamFile(file, contentType);

    file.close();
}

void handleBackgroundImage()
{
    sendFile("/images/background.jpg", "image/jpeg");
}

void handleGasImage()
{
    sendFile("/images/gas.png", "image/png");
}

void handleWheelImage(){
    sendFile("/images/wheel.png", "image/png");
}

void handleWindowScript()
{
    printlnLog("Handling window script.");

    String content = readFileString("/js/window.js");

    server.send(200, "application/javascript", content);
}

void handleGasScript()
{
    printlnLog("Handling gas script.");

    String content = readFileString("/js/gas.js");

    server.send(200, "application/javascript", content);
}

void handleWheelScript()
{
    printlnLog("Handling wheel script.");

    String content = readFileString("/js/wheel.js");

    server.send(200, "application/javascript", content);
}

void handleGas()
{
    printlnLog("Handling API gas.");

    String gasString = server.arg("gas");
    float gas = gasString.toFloat();
    printLog("gas: ");
    printlnLog(gas);

    setCarGas(gas);

    server.send(200);
}

void handleWheel()
{
    printlnLog("Handling API wheel.");

    String wheelString = server.arg("wheel");
    float wheel = wheelString.toFloat();
    printLog("wheel: ");
    printlnLog(wheel);

    setCarWheel(wheel);

    server.send(200);
}