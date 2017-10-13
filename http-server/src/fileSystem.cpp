#include "Includes.h"

FileSystem::FileSystem(Logger *logger)
{
    _logger = logger;
}

bool FileSystem::setup()
{
    SPIFFS.begin();

    _logger->println("File system successfully inititalized.");

    return true;
}

String FileSystem::readAsString(String path)
{
    File file = SPIFFS.open(path, "r");

    String result = file.readStringUntil('\0');

    _logger->print("Open file at ");
    _logger->print(path);
    _logger->print(" result: ");
    _logger->println((long)file.size());

    file.close();

    return result;
}