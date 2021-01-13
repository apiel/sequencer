unsigned long gBtnTimeLast = 0;

byte gBtnDouble = 0;
unsigned long gBtnTimeLastDouble = 0;

bool isPressed(int pin, int val = HIGH) {
    int btn = digitalRead(pin);
    return btn == val;
}

bool isDoubleClick(int pin, int ms = 500, int val = HIGH) {
    bool pressed = isPressed(pin, val);
    if (gBtnDouble == 0 && pressed) {
        gBtnDouble = 1;
        gBtnTimeLastDouble = millis();
    } else if (gBtnDouble > 0 && millis() - gBtnTimeLastDouble < ms) {
        if (gBtnDouble == 1 && !pressed) {
            gBtnDouble = 2;
        } else if (gBtnDouble == 2 && pressed) {
            gBtnDouble = 3;
        } else if (gBtnDouble == 3 && !pressed) {
            gBtnDouble = 0;
            return true;
        }
    } else {
        gBtnDouble = 0;
    }
    return false;
}

// basic click
bool isClick(int pin, int ms = 200, int val = HIGH) {
    if (millis() - gBtnTimeLast > ms) {
        if (isPressed(pin, val)) {
            gBtnTimeLast = millis();
            return true;
        }
    }
    return false;
}
