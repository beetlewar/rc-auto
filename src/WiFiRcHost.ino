#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

bool setupRcHost()
{
    server.begin();

    server.on("/", handleRoot);

    server.onNotFound(handleNotFound);

    Serial.println("Http server started at port 80.");

    return true;
}

void loopRcHost()
{
    server.handleClient();
}

void handleRoot()
{
    Serial.println("Handling root.");

    String content = readFileString("/Index.html");

    server.send(200, "text/html", content);
}

void handleNotFound()
{
    Serial.println("Handling not found.");

    server.send(404, "text/plain", "Not found");
}