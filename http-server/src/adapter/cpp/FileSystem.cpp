#include "..\..\Includes.h"

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

File FileSystem::openRead(String path)
{
    File file = SPIFFS.open(path, "r");

    _logger->print("Opened file at ");
    _logger->print(path);
    _logger->print(", size: ");
    _logger->println((long)file.size());

    return file;
}