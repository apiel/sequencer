#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_W 128  // OLED display width, in pixels
#define SCREEN_H 64   // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, OLED_RST);

char buf[SCREEN_W];

EventDelay displayDelay;

void displaySetup() {
    // reset OLED display via software
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(20);
    digitalWrite(OLED_RST, HIGH);

    // initialize OLED
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false,
                       false)) {  // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;  // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SEQUENCER");

    displayUpdate();
}

void displayUpdate() {
    if (displayDelay.ready()) {
        if (isPhaseMenu()) {
            displayPhase();
        } else {
            displayMainMenu();
        }
        displayStatus();
        display.display();
        // displayDelay.start(150);
        displayDelay.start(gTempo / 2);
    }
}

void displayStatus() {
    if (gSeqPlay) {
        display.fillTriangle(100, 0, 106, 3, 100, 7, WHITE);
    } else {
        display.fillRect(100, 1, 6, 6, WHITE);
    }
    // dprintxy(18, 0, "%d", gSeqStepIndex+1);
    for (byte i = 0; i < gSeqStepIndex + 1; i++) {
        // display.fillRect(68 + (i%8) * 4, i >= 8 ? 0 : 5, 2, 2, WHITE);
        byte y = 0;
        if (i > 11)
            y = 6;
        else if (i > 7)
            y = 4;
        else if (i > 3)
            y = 2;
        display.fillRect(82 + (i % 4) * 4, y, 2, 1, WHITE);
    }
    display.drawTriangle(110, 6, 127, 6, 127, 0, WHITE);
    display.fillTriangle(110, 6, 110 + (17 * gVolume / MAX_VOLUME), 6,
                         110 + (17 * gVolume / MAX_VOLUME),
                         6 - (6 * gVolume / MAX_VOLUME), WHITE);

    if (gMcMode) {
        display.setCursor(66, 0);
        display.setTextColor(BLACK, WHITE);
        display.print("mc");
        display.setTextColor(WHITE);
        display.drawLine(65, 0, 65, 7, WHITE);
    }
}

void displayMainMenu() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Main menu");
    display.println("");
    dprintln("BPM: %d", gBPM);
    dprintln("Pattern: %d", gCurrentPatternId);
    dprintln("Setup: %d", gCurrentPhasesSetup);
    displayLpf();
}

Phase<MAX_NUM_CELLS, STEP_COUNT> *getCurrentPhase() {
    return &phases[getCurrentPhaseIdx()];
}

void displayPhase() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Phase %c", getCurrentPhaseChar());

    Phase<MAX_NUM_CELLS, STEP_COUNT> *phase = getCurrentPhase();

    display.println(phase->tableName);
    dprintln("Freq %d", phase->frequency);
    if (gMcMode) {
        dprintln("%d-> %d", gStepMode + 1, phase->freqSteps[gStepMode]);
    }

    dprintxyAbs(4, 32, "A");
    dprintxyTimePct(0, 40, phase->envlop.getTime(0));
    dprintxyLevelPct(0, 48, phase->envlop.getLevel(0));

    display.drawLine(15, 32, 15, 55, WHITE);

    dprintxyAbs(21, 32, "S");
    dprintxyTimePct(17, 40, phase->envlop.getTime(1));
    dprintxyLevelPct(17, 48, phase->envlop.getLevel(1));

    display.drawLine(31, 32, 31, 55, WHITE);

    dprintxyAbs(37, 32, "D");
    dprintxyTimePct(33, 40, phase->envlop.getTime(2));
    dprintxyLevelPct(33, 48, phase->envlop.getLevel(2));

    if (phase->type > REVERB) {
        if (gMcMode) {
            display.fillTriangle(82, 33, 82, 38, 84, 35, WHITE);
            display.fillTriangle(98, 33, 98, 38, 100, 35, WHITE);
            display.fillTriangle(114, 33, 114, 38, 116, 35, WHITE);
        } else {
            display.fillTriangle(0, 33, 0, 38, 2, 35, WHITE);
            display.fillTriangle(17, 33, 17, 38, 19, 35, WHITE);
            display.fillTriangle(33, 33, 33, 38, 35, 35, WHITE);
        }

        dprintxyAbs(86, 32, "A");
        dprintxyTimePct(81, 40, phase->envlopFreq.getTime(0));
        dprintxyLevelPct(81, 48, phase->envlopFreq.getLevel(0));

        display.drawLine(95, 32, 95, 55, WHITE);

        dprintxyAbs(102, 32, "S");
        dprintxyTimePct(97, 40, phase->envlopFreq.getTime(1));
        dprintxyLevelPct(97, 48, phase->envlopFreq.getLevel(1));

        display.drawLine(111, 32, 111, 55, WHITE);

        dprintxyAbs(118, 32, "D");
        dprintxyTimePct(113, 40, phase->envlopFreq.getTime(2));
        dprintxyLevelPct(113, 48, phase->envlopFreq.getLevel(2));

        if (phase->type == FREQ_ENV) {
            dprintxy(12, 1, "Freq Env");
            dprintxy(12, 2, "Shift %d", phase->freqShift);
        } else if (phase->type == PHASOR2) {
            dprintxy(12, 1, "Phasor 2");
            dprintxy(12, 2, "Shift %d", phase->phasorShift);
        } else if (phase->type == PHASOR3) {
            dprintxy(12, 1, "Phasor 3");
            dprintxy(12, 2, "Shift %d", phase->phasorShift);
        }
        dprintxy(12, 3, "LR %d", phase->envlopFreq.getLerpRate());
    } else {
        if (phase->type == REVERB) {
            dprintxy(12, 1, "Reverb");
        } else {
            dprintxy(12, 1, "Simple");
        }
    }
    displayPhasePattern();
}

void displayPhasePattern() {
    byte idx = getCurrentPhaseIdx();

    for (byte i = 0, s = 0; i < STEP_COUNT; i++) {
        if (i % 4 == 0) s += 3;
        int aPhase = gCurrentPattern[i];
        if (aPhase & (int)pow(2, idx)) {
            display.fillRect(i * 7 + s, 57, 6, 6, WHITE);
        } else {
            display.drawRect(i * 7 + s, 57, 6, 6, WHITE);
        }
        if (i == gSeqStepIndex) {
            display.drawLine(i * 7 + 1 + s, 63, i * 7 + 4 + s, 63, WHITE);
        }
    }
}

void displayLpf() {
    dprintln("Cutoff: %d", gCutoff);
    dprintln("Resonance: %d", gResonance);
}

void dprintxyLevelPct(byte x, byte y, byte level) {
    if (level == 255) {
        display.setCursor(x + 4, y);
        display.print(1);
    } else {
        int value = (float)level / 255 * 100;
        display.setCursor(x + 2, y);
        display.print(value);
        display.drawPixel(x, y + 6, WHITE);
    }
}

void dprintxyTimePct(byte x, byte y, unsigned int ms) {
    float value = (float)ms / gTempo;
    if (value < 1) {
        byte f = value * 10;
        display.setCursor(x + 2, y);
        display.print(f);
        display.drawPixel(x, y + 6, WHITE);
    } else {
        display.setCursor(x, y);
        byte i = (byte)value;
        display.print(i);
        display.setCursor(x + 8, y);
        byte f = (value - i) * 10;
        display.print(f);
        display.drawPixel(x + 6, y + 6, WHITE);
    }
}

void dprintxyAbs(byte x, byte y, const char *str, ...) {
    display.setCursor(x, y);
    va_list argptr;
    va_start(argptr, str);
    vsnprintf(buf, SCREEN_W, str, argptr);
    va_end(argptr);
    display.print(buf);
}

void dprintxy(byte x, byte y, const char *str, ...) {
    display.setCursor(6 * x, 8 * y);
    va_list argptr;
    va_start(argptr, str);
    vsnprintf(buf, SCREEN_W, str, argptr);
    va_end(argptr);
    display.print(buf);
}

void dprint(const char *str, ...) {
    va_list argptr;
    va_start(argptr, str);
    vsnprintf(buf, SCREEN_W, str, argptr);
    va_end(argptr);
    display.print(buf);
}

void dprintln(const char *str, ...) {
    va_list argptr;
    va_start(argptr, str);
    vsnprintf(buf, SCREEN_W, str, argptr);
    va_end(argptr);
    display.println(buf);
}
