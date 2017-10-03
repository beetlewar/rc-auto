#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

bool setupRcHost()
{
    server.begin();

    server.onNotFound(handleNotFound);

    server.on("/", HTTP_GET, handleRoot);
    server.on("/images/background.jpg", handleBackgroundImage);
    server.on("/images/gas.png", handleGasImage);
    server.on("/js/gas.js", HTTP_GET, handleGasScript);
    server.on("/js/rotation.js", HTTP_GET, handleRotationScript);
    server.on("/api/gas", HTTP_PUT, handleGas);
    server.on("/api/rotation", HTTP_PUT, handleRotation);

    Serial.println("Http server started at port 80.");

    return true;
}

void loopRcHost()
{
    server.handleClient();
}

void handleNotFound()
{
    Serial.println("Handling not found.");

    server.send(404, "text/plain", "Not found");
}

void handleRoot()
{
    Serial.println("Handling index.hml.");

    String content = readFileString("/Index.html");

    server.send(200, "text/html", content);
}

void handleBackgroundImage()
{
    Serial.println("Handling background image.");

    String content = readFileString("/images/background.jpg");

    server.send(200, "text/plain", "hello back image");
}

void handleGasImage()
{
    Serial.println("Handling gas image.");

    String content = readFileString("/images/gas.png");

    server.send(200, "text/plain", "hello gas image");
}

void handleGasScript()
{
    Serial.println("Handling gas script.");

    String content = readFileString("/js/gas.js");

    server.send(200, "application/javascript", content);
}

void handleRotationScript()
{
    Serial.println("Handling rotation script.");

    String content = readFileString("/js/rotation.js");

    server.send(200, "application/javascript", content);
}

void handleGas()
{
    Serial.println("Handling API gas.");

    String gasString = server.arg("gas");
    float gas = gasString.toFloat();
    Serial.print("gas: ");
    Serial.println(gas);

    setCarGas(gas);

    server.send(200);
}

void handleRotation()
{
    Serial.println("Handling API rotation.");

    String rotationString = server.arg("rotation");
    float rotation = rotationString.toFloat();
    Serial.print("rotation: ");
    Serial.println(rotation);

    setCarRotation(rotation);

    server.send(200);
}