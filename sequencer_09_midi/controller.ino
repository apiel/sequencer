#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

#ifdef WEMOS_BOARD
#define PIN_BTN_1 5   // d1
#define PIN_BTN_2 16  // d0
#define PIN_BTN_3 0   // d3
#else
#define PIN_BTN_1 39
#define PIN_BTN_2 38
#define PIN_BTN_3 0
#endif

#define OPTION_COUNT 5

typedef struct {
    const char* name;
    unsigned int (*fn)(int val, int isInc);
    unsigned int val;
    const char* unit = "";
} Option;

Option gOption[OPTION_COUNT];

unsigned int gSelected = 0;

#define SEL_MOD_MENU 1
#define SEL_MOD_VALUE 2
byte gSelMod = SEL_MOD_VALUE;

void controllerSetup() {
    pinMode(PIN_BTN_1, INPUT);
    pinMode(PIN_BTN_2, INPUT);
    pinMode(PIN_BTN_3, INPUT);

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
    display.print("SEQUENCER");
    display.display();

    gOption[0].name = "Play";
    gOption[0].fn = &fnPlay;
    gOption[1].name = "Mute";
    gOption[1].fn = &fnMute;
    gOption[2].name = "BPM";
    gOption[2].fn = &fnBPM;
    gOption[3].name = "Sequence gate";
    gOption[3].unit = "%";
    gOption[3].fn = &fnSeqGate;
    gOption[4].name = "Pattern";
    gOption[4].fn = &fnPattern;

    for (int i = 0; i < OPTION_COUNT; i++) {
        gOption[i].val = callFn(i, 0, true);
    }

    updateDisplay();
}

void controllerHandler() {
    setSelector();
    setValue();
}

int mod(int n, int m) { return ((n % m) + m) % m; }

void updateDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);
    if (gSelMod == SEL_MOD_MENU) {
        display.println("# menu #");
    } else if (gSelMod == SEL_MOD_VALUE) {
        display.println("# value #");
    }
    displayPrintRow(mod(gSelected + 3, OPTION_COUNT));
    displayPrintRow(mod(gSelected + 2, OPTION_COUNT));
    displayPrintRow(mod(gSelected + 1, OPTION_COUNT));
    display.print(">");
    displayPrintRow(gSelected);
    displayPrintRow(mod(gSelected - 1, OPTION_COUNT));
    displayPrintRow(mod(gSelected - 2, OPTION_COUNT));
    displayPrintRow(mod(gSelected - 3, OPTION_COUNT));
    display.display();
}

void displayPrintRow(int row) {
    display.print(gOption[row].name);
    display.print(": ");
    display.print(gOption[row].val);
    display.println(gOption[row].unit);
}

void setSelMod(byte selMod) {
    if (gSelMod != selMod) {
        gSelMod = selMod;
        updateDisplay();
    }
}

// maybe we should do click sel + up or down for menu selection
// and still double click sel to switch (to) category (selection)
void setSelector() {
    if (isDoubleClick(PIN_BTN_3, 500, LOW)) {
        Serial.println("double click, switch category");
    } else if (isPressed(PIN_BTN_3, LOW)) {
        if (isClick(PIN_BTN_1, 200)) {
            gSelected = mod(gSelected + 1, OPTION_COUNT);
            updateDisplay();
        } else if (isClick(PIN_BTN_2, 200)) {
            gSelected = mod(gSelected - 1, OPTION_COUNT);
            updateDisplay();
        }
        setSelMod(SEL_MOD_MENU);
    } else {
        setSelMod(SEL_MOD_VALUE);
    }
}

void setValue() {
    if (gSelMod == SEL_MOD_VALUE) {
        bool btn1 = isClick(PIN_BTN_1);
        bool btn2 = isClick(PIN_BTN_2);

        if (btn1 || btn2) {
            int val = btn1 ? 1 : -1;
            callFn(gSelected, val, true);
        }
    }
}

unsigned int callFn(byte fnKey, int val, int isInc) {
    gOption[fnKey].val = (*gOption[fnKey].fn)(val, isInc);
    updateDisplay();

    return gOption[fnKey].val;
}

unsigned int fnPlay(int val, int isInc) {
    // val can be 0 for default initialization
    // if we to have the player off by default then put || val == 0
    if (val == -1) {
        gSeqPlay = false;
        return 0;
    }
    gSeqPlay = true;
    gSeqNoteIndex = 0;
    gSeqTimeCurrent = millis();
    gSeqTimeLast = gSeqTimeCurrent;
    gSeqNoteOn = false;
    return 1;
}

unsigned int fnMute(int val, int isInc) {
    // val can be 0 for default initialization
    // if we want to have the player mute by default then put || val == 0
    if (val == 1) {
        gSeqMute = true;
        return 1;
    }
    gSeqMute = false;
    return 0;
}

unsigned int fnBPM(int val, int isInc) {
    int bpm = getVal(gSeqBase.gSeqBPM, val, isInc);
    gSeqBase.gSeqBPM = between(bpm, 10, 250);
    setTempo();
    return gSeqBase.gSeqBPM;
}

unsigned int fnSeqGate(int val, int isInc) {
    int pct = getVal(gSeqBase.gSeqGatePercent, val, isInc);
    gSeqBase.gSeqGatePercent = between(pct, 0, 100);
    calcGate();
    return gSeqBase.gSeqGatePercent;
}

unsigned int fnPattern(int val, int isInc) {
    gSeqPatternIndex = getVal(gSeqPatternIndex, val, isInc) % MAX_PATTERNS;
    assignCurrentPattern(gSeqPatternIndex);
    return gSeqPatternIndex;
}
