bool loadToneFromStorage(byte toneId) {
    sprintf(storagePath, "/tone_%x\0", toneId);
    Serial.println(storagePath);

    if (!SPIFFS.exists(storagePath)) {
        Serial.println("> no data found for this tone.");
        return false;
    }

    // cleanup for testing purpose
    // SPIFFS.remove(storagePath);

    File file = SPIFFS.open(storagePath);
    if (!file || file.isDirectory()) {
        Serial.println("> no data found for this tone.");
        return false;
    }

    size_t len;
    while (file.available() && assignStorageValues(&file)) {
        if (storageValues[0] == 0) {
            setTable(&tones[toneId], storageValues[1]);
        }
    }
    file.close();
    return true;
}

bool saveToneToStorage(byte toneId) {
    sprintf(storagePath, "/tone_%x\0", toneId);
    File file = SPIFFS.open(storagePath, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return false;
    }
    Tone* pTone = &tones[toneId];
    sprintf(storageBuffer, "0 %d\n\0", pTone->tableId);
    file.print(storageBuffer);
    file.close();
    return true;
}
