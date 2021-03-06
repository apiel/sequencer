#include "SPIFFS.h"
// Look at FS in root file to remove if storage doesn't use FS anymore

#define FORMAT_SPIFFS_IF_FAILED true

#define STORAGE_PATH_LEN 32
#define STORAGE_BUFFER_SIZE 32
#define STORAGE_VALUES_SIZE 20

char storagePath[STORAGE_PATH_LEN];
char storageBuffer[STORAGE_BUFFER_SIZE];
int storageValues[STORAGE_VALUES_SIZE];

void setupStorage() {
    if (!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)) {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    Serial.println("SPIFFS Mounted");
}

// Instead of using len = file.readBytesUntil(' ', ...);
// Let's assign all values of a line into an array
bool assignStorageValues(fs::File* file) {
    char c;
    byte pos = -1;
    byte i = 0;
    while (file->available() && i < STORAGE_VALUES_SIZE) {
        pos++;
        c = file->read();
        storageBuffer[pos] = c;
        if (c == ' ' || c == '\n') {
            storageBuffer[pos] = '\0';
            storageValues[i] = atoi(storageBuffer);
            i++;
            pos = -1;
            if (c == '\n') {
                Serial.print('\n');
                return true;
            }
        }
    }
    return false;
}
