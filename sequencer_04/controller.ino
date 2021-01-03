#define PIN_BTN_1 5   // d1
#define PIN_BTN_2 16  // d0
#define PIN_BTN_3 0   // d3

unsigned long gBtnTimeLast = 0;

void controllerSetup() {
    pinMode(PIN_BTN_1, INPUT);
    pinMode(PIN_BTN_2, INPUT);
    pinMode(PIN_BTN_3, INPUT);
}

void controllerHandler() {
    setSelector();
    setValue();
}

bool isClick(int pin, int ms = 100, int val = HIGH) {
    if (millis() - gBtnTimeLast > ms) {
        int btn = digitalRead(pin);
        if (btn == val) {
            gBtnTimeLast = millis();
            return true;
        }
    }
    return false;
}

void setSelector() {
    if (isClick(PIN_BTN_3, 300, LOW)) {
        gSelected = (gSelected + 1) % 4;
        if (gSelected == 0) {
            Serial.println("play");
        } else if (gSelected == 1) {
            Serial.println("sel BPM");
        } else if (gSelected == 2) {
            Serial.println("sel sequence gate percentage");
        } else if (gSelected == 3) {
            Serial.println("sel pattern");
        }
    }
}

void setValue() {
    bool btn1 = isClick(PIN_BTN_1);
    bool btn2 = isClick(PIN_BTN_2);

    if (btn1 || btn2) {
        int val = btn1 ? 1 : -1;

        if (gSelected == 0) {
            gSeqPlay = btn1;
            Serial.print("Play: ");
            Serial.println(gSeqPlay);
        } else if (gSelected == 1) {
            int bpm = gSeqBase.gSeqBPM + val;
            if (bpm > 10 && bpm < 250) {
                gSeqBase.gSeqBPM = bpm;
                setTempo();
            }
            Serial.print("set BPM: ");
            Serial.println(gSeqBase.gSeqBPM);
        } else if (gSelected == 2) {
            int pct = gSeqBase.gSeqGatePercent + val;
            if (pct > 0 && pct < 99) {
                gSeqBase.gSeqGatePercent = pct;
                calcGate();
            }
            Serial.print("set sequence gate percentage: ");
            Serial.println(gSeqBase.gSeqGatePercent);
        } else if (gSelected == 3) {
            gSeqPatternIndex = (gSeqPatternIndex + val) % MAX_PATTERNS;
            Serial.print("set pattern: ");
            Serial.println(gSeqPatternIndex);
        }
    }
}
