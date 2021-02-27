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

    if (kick.type == PHASOR2 || kick.type == PHASOR3) {
        dprintxy(0, 1, "Shift %d", kick.phasorShift);
    } else {
        dprintxy(0, 1, "Shift %d", kick.freqShift);
    }
    dprintxy(10, 1, "Lerp %d", kick.envlopFreq.getLerpRate());

    if (kick.type != SAMPLE) {
        dprintxyAbs(0, 4 + 2 * 8, "A %d", kick.envlop.getTime(0));
        dprintxyAbs(10 * 6, 4 + 2 * 8, "S %d", kick.envlop.getTime(1));

        dprintxyAbs(0, 4 + 3 * 8, "R %d", kick.envlop.getTime(2));
        dprintxyAbs(10 * 6, 4 + 3 * 8, "Level %d", kick.envlop.getLevel(0));

        dprintxy(0, 5, "T");
        dprintxy(0, 6, "L");
        displayPhase(0);
        displayPhase(1);
        displayPhase(2);
        displayPhase(3);
        displayPhase(4);
        displayPhase(5);
    }
}

void displayPhase(byte id) {
    byte T = 5 * 8;
    byte L = 6 * 8;
    byte x = 10 + id * 18;

    display.drawLine(x, T, x, L + 8, WHITE);

    dprintxyTimePct(
        x + 2, T,
        (float)kick.envlopFreq.getTime(id) / (float)kick.envlop.getTotalTime());
    // dprintxyLevelPct(113, 48, kick.envlopFreq.getLevel(2));
}

// todo
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

void dprintxyTimePct(byte x, byte y, float value) {
    if (value < 1) {
        byte f = value * 100;
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
