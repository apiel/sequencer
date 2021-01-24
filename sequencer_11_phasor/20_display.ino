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

void displayPhase() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Phase %c", getCurrentPhaseChar());
    byte phase = getCurrentPhase();

    for (int i = 0; i < 8; i++) {
        display.drawLine(i * 16 - 1, 32, i * 16 - 1, 55, WHITE);
    }
    dprintxyAbs(4, 32, "A");
    dprintxyFloat(0, 40, 0.35);
    dprintxyFloat(0, 48, 1.56);
    
    dprintxyAbs(20, 32, "D");
    dprintxyFloat(17, 40, 2.35);
    dprintxyFloat(17, 48, 1.56);
    
    dprintxyAbs(36, 32, "S");
    dprintxyAbs(52, 32, "R");
    dprintxyAbs(68, 32, "A");
    dprintxyAbs(84, 32, "D");
    dprintxyAbs(100, 32, "S");
    dprintxyAbs(116, 32, "R");

    // dprintln("A %.1f", (float)phases[phase].adsr.getTime(ATTACK) / gTempo);
    // dprintln("D %.1f", (float)phases[phase].adsr.getTime(DECAY) / gTempo);
    // dprintln("S %.1f", (float)phases[phase].adsr.getTime(SUSTAIN) / gTempo);
    // dprintln("R %.1f", (float)phases[phase].adsr.getTime(RELEASE) / gTempo);
    // dprintln("P %d", phases[phase].adsr.getLevel(ATTACK));
    // dprintln("S %d", phases[phase].adsr.getLevel(SUSTAIN));

    // if (gPhase[phase].useFreqEnvelope) {
    //     dprintxy(6, 1, "A %d", gPhase[phase].AFreqTime);
    //     dprintxy(6, 2, "S %d", gPhase[phase].SFreqTime);
    //     dprintxy(6, 3, "R %d", gPhase[phase].RFreqTime);
    //     dprintxy(6, 4, "A %d", gPhase[phase].adsrFreq.getLevel(ATTACK));
    //     dprintxy(6, 5, "S %d", gPhase[phase].adsrFreq.getLevel(SUSTAIN));
    //     dprintxy(6, 6, "R %d", gPhase[phase].adsrFreq.getLevel(RELEASE));
    //     dprintxy(12, 3, "Shift %d", gPhase[phase].freqShift);
    // }

    // dprintxy(12, 1, "%s", phases[phase].tableName);
    // dprintxy(12, 2, "Freq %d", phases[phase].frequency);
    displayPhasePattern(phase);
}

void displayPhasePattern(byte phase) {
    for (byte i = 0, s = 0; i < MAX_PHASES; i++) {
        if (i % 4 == 0) s += 3;
        int aPhase = gCurrentPattern[i];
        if (aPhase & (int)pow(2, phase)) {
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
    display.setCursor(x, y);
    byte i = (byte) value;
    byte f = (value - i) * 10;
    display.print(i);
    display.setCursor(x + 8, y);
    display.print(f);
    display.drawPixel(x + 6, y + 6, WHITE);
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
