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
        if (isNoteMenu()) {
            displayNote();
        } else {
            displayMainMenu();
        }
        displayStatus();
        display.display();
        displayDelay.start(150);
    }
}

void displayStatus() {
    if (gSeqPlay) {
        display.fillTriangle(122, 0, 128, 3, 122, 7, WHITE);
    } else {
        display.fillRect(122, 1, 6, 6, WHITE);
    }
    dprintxy(18, 0, "%d", gSeqNoteIndex+1);
}

void displayMainMenu() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Main menu");
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
