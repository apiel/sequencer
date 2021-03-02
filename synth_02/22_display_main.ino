void displayMainMenu() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Main menu");
    display.println("");
    dprintln("BPM: %d", gBPM);
    // dprintln("Pattern: %d", gCurrentPatternId);
    dprintln("Setup: %d", gCurrentTonesSetup);
    displayLpf();
}
