#include "Includes.h"

FileSystem::FileSystem(Logger *logger)
{
    _logger = logger;
}

bool FileSystem::setup()
{
    SPIFFS.begin();

    _logger->println("File system successfully inititalized.");

    int cnt = 0;
    Dir dir = SPIFFS.openDir("");
    while (dir.next())
    {
        File f = dir.openFile("r");
        _logger->println(dir.fileName() + ": " + String(f.size()));
        cnt++;
    }

    _logger->println("Count files: " + String(cnt));

    return true;
}

File FileSystem::openRead(String path)
{
    File file = SPIFFS.open(path, "r");

    if (!file)
    {
        _logger->println("Failed to open file " + path);
    }
    else
    {
        _logger->print("Opened file at ");
        _logger->print(path);
        _logger->print(", size: ");
        _logger->println((long)file.size());
    }

    return file;
}