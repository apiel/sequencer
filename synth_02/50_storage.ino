#include "FS.h"
#include "SPIFFS.h"

#define FORMAT_SPIFFS_IF_FAILED true

#define STORAGE_PATH_LEN 32
#define STORAGE_BUFFER_SIZE 32

char storagePath[STORAGE_PATH_LEN];
char storageBuffer[STORAGE_BUFFER_SIZE];

void setupStorage() {
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    Serial.println("SPIFFS Mounted");
}
