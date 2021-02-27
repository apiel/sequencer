#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EventDelay.h>
#include <Wire.h>

// OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_W 128  // OLED display width, in pixels
#define SCREEN_H 64   // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, OLED_RST);

EventDelay displayDelay;
bool gMcMode = false;

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

    displayUpdate();
}

void displayUpdate() {
    if (displayDelay.ready()) {
        displayKick();
        display.display();
        displayDelay.start(100);
    }
}

void displayKick() {
    display.clearDisplay();
    display.setCursor(0, 0);

    display.println(kick.tableName);
    dprintxy(10, 0, "%d", kick.frequency);
    if (kick.type == REVERB) {
        dprintxy(15, 0, "Reverb");
    } else if (kick.type == SAMPLE) {
        dprintxy(15, 0, "Sample");
    } else if (kick.type == PHASOR2) {
        dprintxy(14, 0, "Phasor2");
    } else if (kick.type == PHASOR3) {
        dprintxy(14, 0, "Phasor3");
    } else {
        dprintxy(15, 0, "Simple");
    }

    if (gMcMode) {
        // dprintln("%d-> %d", gStepMode + 1, kick.freqSteps[gStepMode]);
    }

    // todo no substain
    // todo sample

    dprintxyAbs(4, 32, "A");
    dprintxyTimePct(0, 40, kick.envlop.getTime(0));
    dprintxyLevelPct(0, 48, kick.envlop.getLevel(0));

    display.drawLine(15, 32, 15, 55, WHITE);

    dprintxyAbs(21, 32, "S");
    dprintxyTimePct(17, 40, kick.envlop.getTime(1));
    dprintxyLevelPct(17, 48, kick.envlop.getLevel(1));

    display.drawLine(31, 32, 31, 55, WHITE);

    dprintxyAbs(37, 32, "D");
    dprintxyTimePct(33, 40, kick.envlop.getTime(2));
    dprintxyLevelPct(33, 48, kick.envlop.getLevel(2));

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
    dprintxyTimePct(81, 40, kick.envlopFreq.getTime(0));
    dprintxyLevelPct(81, 48, kick.envlopFreq.getLevel(0));

    display.drawLine(95, 32, 95, 55, WHITE);

    dprintxyAbs(102, 32, "S");
    dprintxyTimePct(97, 40, kick.envlopFreq.getTime(1));
    dprintxyLevelPct(97, 48, kick.envlopFreq.getLevel(1));

    display.drawLine(111, 32, 111, 55, WHITE);

    dprintxyAbs(118, 32, "D");
    dprintxyTimePct(113, 40, kick.envlopFreq.getTime(2));
    dprintxyLevelPct(113, 48, kick.envlopFreq.getLevel(2));

    dprintxy(12, 2, "Shift %d", kick.freqShift);
    dprintxy(12, 3, "LR %d", kick.envlopFreq.getLerpRate());
}

// todo
void displayLpf() {
    dprintln("Cutoff: %d", gCutoff);
    dprintln("Resonance: %d", gResonance);
}
