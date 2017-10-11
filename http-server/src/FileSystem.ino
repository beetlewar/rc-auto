#include "FS.h"

bool setupFileSystem()
{
    SPIFFS.begin();

    printlnLog("File system successfully inititalized.");

    return true;
}

String readFileString(String path)
{
    File file = SPIFFS.open(path, "r");

    String result = file.readStringUntil('\0');

    printLog("Open file at ");
    printLog(path);
    printLog(" result: ");
    printlnLog(file);

    file.close();

    return result;
}