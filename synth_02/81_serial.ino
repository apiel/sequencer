void handleSerial() {
    if (Serial.available()) {
        int data = Serial.read();
        if (data == ':') {
            Serial.read();
            byte type = Serial.read();
            byte key = Serial.read();
            byte val = Serial.read();
            Serial.print("received midi ");
            Serial.print(type, DEC);
            Serial.print(" ");
            Serial.print(key, DEC);
            Serial.print(" ");
            Serial.println(val, DEC);
            handleMidi(type, key, val);
        } else {
            Serial.print("I received: ");
            Serial.println(data);
        }
        // } else {
        // Serial.print(".");
    }
}
