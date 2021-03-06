bool loadPatternFromStorage(byte toneId, byte patternId) {
    sprintf(storagePath, "/pattern_%x_%x\0", toneId, patternId);
    Serial.println(storagePath);

    if (!SPIFFS.exists(storagePath)) {
        Serial.println("> no data found for this pattern.");
        return false;
    }

    // cleanup for testing purpose
    // SPIFFS.remove(storagePath);

    File file = SPIFFS.open(storagePath);
    if (!file || file.isDirectory()) {
        Serial.println("> no data found for this pattern.");
        return false;
    }

    size_t len;
    while (file.available() && assignStorageValues(&file)) {
        // len = file.readBytesUntil(' ', storageBuffer, STORAGE_BUFFER_SIZE);
        // storageBuffer[len] = 0;
        // byte pos = (byte)atoi(storageBuffer);
        // len = file.readBytesUntil(' ', storageBuffer, STORAGE_BUFFER_SIZE);
        // storageBuffer[len] = 0;
        // byte note = (byte)atoi(storageBuffer);
        // len = file.readBytesUntil(' ', storageBuffer, STORAGE_BUFFER_SIZE);
        // storageBuffer[len] = 0;
        // byte duration = (byte)atoi(storageBuffer);
        // file.readBytesUntil('\n', storageBuffer, STORAGE_BUFFER_SIZE);
        // bool slide = storageBuffer[0] == '1';
        patterns[toneId][patternId].add(
            (byte)storageValues[0], (byte)storageValues[1],
            (byte)storageValues[2], storageValues[3] == 1);
    }
    file.close();

    patterns[toneId][patternId].print();

    return true;
}

bool savePatternToStorage(byte toneId, byte patternId) {
    sprintf(storagePath, "/pattern_%x_%x\0", toneId, patternId);
    File file = SPIFFS.open(storagePath, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return false;
    }
    Pattern* pattern = &patterns[toneId][patternId];
    for (byte pos = 0; pos < MAX_STEPS_IN_PATTERN; pos++) {
        Step* step = &pattern->steps[pos];
        sprintf(storageBuffer, "%d %d %d %d\n\0", (int)pos, (int)step->note,
                (int)step->duration, step->slide ? 1 : 0);
        // Serial.println(storageBuffer);
        file.print(storageBuffer);
    }
    // Serial.println("-");
    file.close();
    return true;
}
