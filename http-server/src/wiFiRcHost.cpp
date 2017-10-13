#include "ESP8266WebServer.h"
#include "FS.h"

extern void printLog(String s);
extern void printlnLog(String s);
extern void printlnLog(float f);
extern String readFileString(String path);
extern void setCarWheel(float value);
extern void setCarGas(float value);

ESP8266WebServer server(80);

void loopRcHost()
{
    server.handleClient();
}

void handleNotFound()
{
    printlnLog("Handling 'not found'.");

    server.send(404, "text/plain", "Not found");
}

void handleRoot()
{
    printlnLog("Handling Index.html.");

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

void handleWheelImage()
{
    sendFile("/images/wheel.png", "image/png");
}

void handleAppScript()
{
    printlnLog("Handling app script.");

    String content = readFileString("/app.js");

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

bool setupRcHost()
{
    server.begin();

    server.on("/", HTTP_GET, handleRoot);
    server.on("/images/background.jpg", handleBackgroundImage);
    server.on("/images/gas.png", handleGasImage);
    server.on("/images/wheel.png", handleWheelImage);
    server.on("/app.js", HTTP_GET, handleAppScript);
    server.on("/api/gas", HTTP_PUT, handleGas);
    server.on("/api/wheel", HTTP_PUT, handleWheel);

    printlnLog("Http server started at port 80.");

    return true;
}