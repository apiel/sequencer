bool loadPatternFromStorage(byte toneId, byte patternId) {
    sprintf(storagePath, "/pattern_%x_%x\0", toneId, patternId);
    Serial.println(storagePath);

    if (!SPIFFS.exists(storagePath)) {
        Serial.println("> no data found for this pattern.");
        return false; 
    }

    File file = SPIFFS.open(storagePath);
    if (!file || file.isDirectory()) {
        Serial.println("> no data found for this pattern.");
        return false;
    }

    size_t len;
    while (file.available()) {
        len = file.readBytesUntil(' ', storageBuffer, STORAGE_BUFFER_SIZE);
        storageBuffer[len] = 0;
        Serial.printf("pos %s\n", storageBuffer);
        byte pos = (byte)atoi(storageBuffer);
        len = file.readBytesUntil(' ', storageBuffer, STORAGE_BUFFER_SIZE);
        storageBuffer[len] = 0;
        Serial.printf("note %s\n", storageBuffer);
        byte note = (byte)atoi(storageBuffer);
        len = file.readBytesUntil(' ', storageBuffer, STORAGE_BUFFER_SIZE);
        storageBuffer[len] = 0;
        Serial.printf("duration %s\n", storageBuffer);
        byte duration = (byte)atoi(storageBuffer);
        file.readBytesUntil('\n', storageBuffer, STORAGE_BUFFER_SIZE);
        bool slide = storageBuffer[0] == '1';
        Serial.printf("slide %s\n", storageBuffer);
        patterns[toneId][patternId].add(pos, note, duration, slide);
        Serial.println("-");
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
        sprintf(storageBuffer, "%x %x %x %d\n\0", pos, step->note,
                step->duration, step->slide);
        file.print(storageBuffer);
    }
    file.close();
    return true;
}
