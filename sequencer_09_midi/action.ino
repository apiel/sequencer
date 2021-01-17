
void play() {
    gSeqPlay = true;
    gSeqNoteIndex = 0;
    gSeqTimeCurrent = millis();
    gSeqTimeLast = gSeqTimeCurrent;
    gSeqNoteOn = false;
}

void stop() { gSeqPlay = false; }

void setBPM(int direction) {
    gSeqBase.gSeqBPM = between(gSeqBase.gSeqBPM + direction, 10, 250);
    Serial.print("Set new bpm");
    Serial.println(gSeqBase.gSeqBPM);
    setTempo();
}

// unsigned int fnSeqGate(int val, int isInc) {
//     int pct = getVal(gSeqBase.gSeqGatePercent, val, isInc);
//     gSeqBase.gSeqGatePercent = between(pct, 0, 100);
//     calcGate();
//     return gSeqBase.gSeqGatePercent;
// }

// unsigned int fnPattern(int val, int isInc) {
//     gSeqPatternIndex = getVal(gSeqPatternIndex, val, isInc) % MAX_PATTERNS;
//     assignCurrentPattern(gSeqPatternIndex);
//     return gSeqPatternIndex;
// }
