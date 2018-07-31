#pragma once

#include "Includes.h"

class FileSystem
{
  private:
    Logger *_logger;

  public:
    FileSystem(Logger *logger);

    bool setup();

    File openRead(String path);

    void writeContent(String path, String content);
};