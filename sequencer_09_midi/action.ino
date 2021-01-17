
void play() {
    gSeqPlay = true;
    gSeqNoteIndex = 0;
    gSeqTimeCurrent = millis();
    gSeqTimeLast = gSeqTimeCurrent;
    gSeqNoteOn = false;
}

void stop() { gSeqPlay = false; }

// unsigned int fnBPM(int val, int isInc) {
//     int bpm = getVal(gSeqBase.gSeqBPM, val, isInc);
//     gSeqBase.gSeqBPM = between(bpm, 10, 250);
//     setTempo();
//     return gSeqBase.gSeqBPM;
// }

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
