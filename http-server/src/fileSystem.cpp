#include "FS.h"

extern void printLog(String s);
extern void printlnLog(String s);
extern void printlnLog(float f);

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
    printlnLog(file.size());

    file.close();

    return result;
}