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
        if (isDrumMenu()) {
            displayDrum();
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
    // dprintxy(18, 0, "%d", gSeqDrumIndex+1);
    for (byte i = 0; i < gSeqDrumIndex + 1; i++) {
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
    dprintln("Pattern: %d", getCurrentPatternId());
    displayLpf();
}

void displayDrum() {
    display.clearDisplay();
    display.setCursor(0, 0);
    dprintln("Drum %c", getCurrentDrumChar());
    byte drum = getCurrentDrum();
    dprintln("A %.1f", (float)phases[drum].adsr.getTime(ATTACK) / gTempo);
    dprintln("D %.1f", (float)phases[drum].adsr.getTime(DECAY) / gTempo);
    dprintln("S %.1f", (float)phases[drum].adsr.getTime(SUSTAIN) / gTempo);
    dprintln("R %.1f", (float)phases[drum].adsr.getTime(RELEASE) / gTempo);
    dprintln("P %d", phases[drum].adsr.getLevel(ATTACK));
    dprintln("S %d", phases[drum].adsr.getLevel(SUSTAIN));

    // if (gDrum[drum].useFreqEnvelope) {
    //     dprintxy(6, 1, "A %d", gDrum[drum].AFreqTime);
    //     dprintxy(6, 2, "S %d", gDrum[drum].SFreqTime);
    //     dprintxy(6, 3, "R %d", gDrum[drum].RFreqTime);
    //     dprintxy(6, 4, "A %d", gDrum[drum].adsrFreq.getLevel(ATTACK));
    //     dprintxy(6, 5, "S %d", gDrum[drum].adsrFreq.getLevel(SUSTAIN));
    //     dprintxy(6, 6, "R %d", gDrum[drum].adsrFreq.getLevel(RELEASE));
    //     dprintxy(12, 3, "Shift %d", gDrum[drum].freqShift);
    // }

    dprintxy(12, 1, "%s", phases[drum].name);
    dprintxy(12, 2, "Freq %d", phases[drum].frequency);
    displayDrumPattern(drum);
}

void displayDrumPattern(byte drum) {
    for (byte i = 0, s = 0; i < MAX_DRUMS; i++) {
        if (i % 4 == 0) s += 3;
        int aDrum = gCurrentPattern[i];
        if (aDrum & (int)pow(2, drum)) {
            display.fillRect(i * 7 + s, 57, 6, 6, WHITE);
        } else {
            display.drawRect(i * 7 + s, 57, 6, 6, WHITE);
        }
        if (i == gSeqDrumIndex) {
            display.drawLine(i * 7 + 1 + s, 63, i * 7 + 4 + s, 63, WHITE);
        }
    }
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
