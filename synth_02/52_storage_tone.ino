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
        switch (storageValues[0]) {
            case 0:
                setTable(&tones[toneId], storageValues[1]);
                break;
            case 1:
                tones[toneId].frequency = storageValues[1];
                break;
            case 2:
                tones[toneId].isDrum = storageValues[1] == 1;
                break;
            case 3:
                tones[toneId].type = (byte)storageValues[1];
                break;
            case 4:
                tones[toneId].freqShift = (byte)storageValues[1];
                break;
            case 5:
                tones[toneId].phasorShift = (byte)storageValues[1];
                break;
            case 6:
                tones[toneId].envlopFreq.setLerpRate(storageValues[1]);
                break;
            case 7:
                tones[toneId].envlop.setTime(0, storageValues[1]);
                tones[toneId].envlop.setLevel(0, (byte)storageValues[2]);
                tones[toneId].envlop.setTime(1, storageValues[3]);
                tones[toneId].envlop.setLevel(1, (byte)storageValues[4]);
                tones[toneId].envlop.setTime(2, storageValues[5]);
                tones[toneId].envlop.setLevel(2, (byte)storageValues[6]);
                break;
            case 8:
                tones[toneId].sample.setStart(storageValues[1]);
                tones[toneId].sample.setEnd(storageValues[2]);
                break;
            case 9:
                tones[toneId].envlopFreq.setTime(0, storageValues[1]);
                tones[toneId].envlopFreq.setLevel(0, (byte)storageValues[2]);
                tones[toneId].envlopFreq.setTime(1, storageValues[3]);
                tones[toneId].envlopFreq.setLevel(1, (byte)storageValues[4]);
                tones[toneId].envlopFreq.setTime(2, storageValues[5]);
                tones[toneId].envlopFreq.setLevel(2, (byte)storageValues[6]);
                tones[toneId].envlopFreq.setTime(3, storageValues[7]);
                tones[toneId].envlopFreq.setLevel(3, (byte)storageValues[8]);
                tones[toneId].envlopFreq.setTime(4, storageValues[9]);
                tones[toneId].envlopFreq.setLevel(4, (byte)storageValues[10]);
                tones[toneId].envlopFreq.setTime(5, storageValues[11]);
                tones[toneId].envlopFreq.setLevel(5, (byte)storageValues[12]);
                tones[toneId].updateFreqTimes();
                break;
            default:
                break;
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
    sprintf(storageBuffer, "0 %d\n\0", (int)pTone->tableId);
    file.print(storageBuffer);
    sprintf(storageBuffer, "1 %d\n\0", pTone->frequency);
    file.print(storageBuffer);
    sprintf(storageBuffer, "2 %d\n\0", pTone->isDrum ? 1 : 0);
    file.print(storageBuffer);
    sprintf(storageBuffer, "3 %d\n\0", (int)pTone->type);
    file.print(storageBuffer);
    sprintf(storageBuffer, "4 %d\n\0", (int)pTone->freqShift);
    file.print(storageBuffer);
    sprintf(storageBuffer, "5 %d\n\0", (int)pTone->phasorShift);
    file.print(storageBuffer);
    sprintf(storageBuffer, "6 %d\n\0", pTone->envlopFreq.getLerpRate());
    file.print(storageBuffer);

    sprintf(storageBuffer, "7 %d %d %d %d %d %d\n\0", pTone->envlop.getTime(0),
            (int)pTone->envlop.getLevel(0), pTone->envlop.getTime(1),
            (int)pTone->envlop.getLevel(1), pTone->envlop.getTime(2),
            (int)pTone->envlop.getLevel(2));
    file.print(storageBuffer);

    sprintf(storageBuffer, "8 %d %d\n\0", pTone->sample.start_pos,
            pTone->sample.end_pos);
    file.print(storageBuffer);

    sprintf(storageBuffer, "9 %d %d %d %d %d %d %d %d %d %d %d %d\n\0",
            pTone->envlopFreq.getTime(0), (int)pTone->envlopFreq.getLevel(0),
            pTone->envlopFreq.getTime(1), (int)pTone->envlopFreq.getLevel(1),
            pTone->envlopFreq.getTime(2), (int)pTone->envlopFreq.getLevel(2),
            pTone->envlopFreq.getTime(3), (int)pTone->envlopFreq.getLevel(3),
            pTone->envlopFreq.getTime(4), (int)pTone->envlopFreq.getLevel(4),
            pTone->envlopFreq.getTime(5), (int)pTone->envlopFreq.getLevel(5));
    file.print(storageBuffer);
    file.close();
    return true;
}
