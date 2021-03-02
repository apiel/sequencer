#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EventDelay.h>
#include <Fonts/Picopixel.h>
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

    Serial.println(tone->tableName);
    // displayUpdate();
}

byte refreshCount = 2;
void displayUpdate() {
    refreshCount = 2;
    displayRefresh();
}

// First print sometime miss pixel, so let's print it several time
void displayRefresh() {
    if (refreshCount > 0 && displayDelay.ready()) {
        refreshCount--;
        displayTone();
        display.display();
        displayDelay.start(100);
    }
}
