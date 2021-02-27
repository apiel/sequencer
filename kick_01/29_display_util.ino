char buf[SCREEN_W];

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
