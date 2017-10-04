#include "FS.h"

bool setupFileSystem()
{
    SPIFFS.begin();

    Serial.println("File system successfully inititalized.");

    Dir dir = SPIFFS.openDir("/");
    while (dir.next())
    {
        Serial.println(dir.fileName());
        File f = dir.openFile("r");
        Serial.println(f.size());
        f.close();
    }

    return true;
}

String readFileString(String path)
{
    File file = SPIFFS.open(path, "r");

    String result = file.readStringUntil('\0');

    Serial.print("Open file at ");
    Serial.print(path);
    Serial.print(" result: ");
    Serial.println(file);

    file.close();

    return result;
}