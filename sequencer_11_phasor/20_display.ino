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
    // dprintxy(18, 0, "%d", gSeqPhaseIndex+1);
    for (byte i = 0; i < gSeqPhaseIndex + 1; i++) {
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
}

void displayMainMenu() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Main menu");
    display.println("");
    dprintln("BPM: %d", gBPM);
    dprintln("Pattern: %d", gCurrentPatternId);
    displayLpf();
}

Phase<MAX_NUM_CELLS> *getCurrentPhase() {
    return &phases[getCurrentPhaseIdx()];
}

void displayPhase() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Phase %c", getCurrentPhaseChar());

    Phase<MAX_NUM_CELLS> *phase = getCurrentPhase();

    display.println(phase->tableName);
    dprintln("Freq %d", phase->frequency);

    dprintxyAbs(4, 32, "A");
    dprintxyFloat(0, 40, (float)phase->adsr.getTime(ATTACK) / gTempo);
    dprintxyFloat(0, 48, (float)phase->adsr.getLevel(ATTACK) / 255);

    display.drawLine(15, 32, 15, 55, WHITE);

    dprintxyAbs(20, 32, "D");
    dprintxyFloat(17, 40, (float)phase->adsr.getTime(DECAY) / gTempo);
    dprintxyFloat(17, 48, (float)phase->adsr.getLevel(DECAY) / 255);

    display.drawLine(31, 32, 31, 55, WHITE);

    dprintxyAbs(36, 32, "S");
    dprintxyFloat(33, 40, (float)phase->adsr.getTime(SUSTAIN) / gTempo);
    dprintxyFloat(33, 48, (float)phase->adsr.getLevel(SUSTAIN) / 255);

    display.drawLine(47, 32, 47, 55, WHITE);

    dprintxyAbs(52, 32, "R");
    dprintxyFloat(49, 40, (float)phase->adsr.getTime(RELEASE) / gTempo);
    dprintxyFloat(49, 48, (float)phase->adsr.getLevel(RELEASE) / 255);

    if (phase->type > SIMPLE) {
        display.drawLine(63, 32, 63, 55, WHITE);

        dprintxyAbs(68, 32, "A");
        dprintxyFloat(65, 40, (float)phase->adsrFreq.getTime(ATTACK) / gTempo);
        dprintxyFloat(65, 48, (float)phase->adsrFreq.getLevel(ATTACK) / 255);

        display.drawLine(79, 32, 79, 55, WHITE);

        dprintxyAbs(84, 32, "D");
        dprintxyFloat(81, 40, (float)phase->adsrFreq.getTime(DECAY) / gTempo);
        dprintxyFloat(81, 48, (float)phase->adsrFreq.getLevel(DECAY) / 255);

        display.drawLine(95, 32, 95, 55, WHITE);

        dprintxyAbs(100, 32, "S");
        dprintxyFloat(97, 40, (float)phase->adsrFreq.getTime(SUSTAIN) / gTempo);
        dprintxyFloat(97, 48, (float)phase->adsrFreq.getLevel(SUSTAIN) / 255);

        display.drawLine(111, 32, 111, 55, WHITE);

        dprintxyAbs(116, 32, "R");
        dprintxyFloat(113, 40,
                      (float)phase->adsrFreq.getTime(RELEASE) / gTempo);
        dprintxyFloat(113, 48, (float)phase->adsrFreq.getLevel(RELEASE) / 255);

        // dprintxy(12, 3, "Shift %d", gPhase[phase].freqShift);
    }
    displayPhasePattern();
}

void displayPhasePattern() {
    byte idx = getCurrentPhaseIdx();

    for (byte i = 0, s = 0; i < MAX_PHASES; i++) {
        if (i % 4 == 0) s += 3;
        int aPhase = gCurrentPattern[i];
        if (aPhase & (int)pow(2, idx)) {
            display.fillRect(i * 7 + s, 57, 6, 6, WHITE);
        } else {
            display.drawRect(i * 7 + s, 57, 6, 6, WHITE);
        }
        if (i == gSeqPhaseIndex) {
            display.drawLine(i * 7 + 1 + s, 63, i * 7 + 4 + s, 63, WHITE);
        }
    }
}

void displayLpf() {
    dprintln("Cutoff: %d", gCutoff);
    dprintln("Resonance: %d", gResonance);
}

void dprintxyFloat(byte x, byte y, float value) {
    if (value < 1) {
        byte f = value * 10;
        display.setCursor(x + 4, y);
        display.print(f);
        display.drawPixel(x + 2, y + 6, WHITE);
    } else {
        display.setCursor(x, y);
        byte i = (byte)value;
        byte f = (value - i) * 10;
        display.print(i);
        display.setCursor(x + 8, y);
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
