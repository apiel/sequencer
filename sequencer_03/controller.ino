unsigned long gBtnTimeLast = 0;

void setSelector() {
  btn3.Update();
  if (btn3.clicks != 0) {
    gSelected = (gSelected + btn3.clicks) % 4;
    if (gSelected == 0) {
      Serial.println("play");
    } else if (gSelected == 1) {
      Serial.println("sel BPM");
    } else if (gSelected == 2) {
      Serial.println("sel sequence gate percentage");
    } else if (gSelected == 3) {
      Serial.println("sel pattern");
    }
  }
}

void setValue() {
  int btn1 = digitalRead(PIN_BTN_1);
  int btn2 = digitalRead(PIN_BTN_2);

  if ((btn1 || btn2) && millis() - gBtnTimeLast > 100) {
    Serial.print("btn: ");
    Serial.print(btn1);
    Serial.print(" - ");
    Serial.println(btn2);
    int val = btn1 ? 1 : -1;

    if (gSelected == 0) {
      //play = true;
      gSeqPlay = btn1 > 0;
      Serial.print("Play: ");
      Serial.println(gSeqPlay);
    } else if (gSelected == 1) {
      int bpm = gSeqBase.gSeqBPM + val;
      if (bpm > 10 && bpm < 250) {
        gSeqBase.gSeqBPM = bpm;
        setTempo();
      }
      Serial.print("set BPM: ");
      Serial.println(gSeqBase.gSeqBPM);
    } else if (gSelected == 2) {
      int pct = gSeqBase.gSeqGatePercent + val;
      if (pct > 0 && pct < 99) {
        gSeqBase.gSeqGatePercent = pct;
        calcGate();
      }
      Serial.print("set sequence gate percentage: ");
      Serial.println(gSeqBase.gSeqGatePercent);
    } else if (gSelected == 3) {

      gSeqPatternIndex = (gSeqPatternIndex + val) % MAX_PATTERNS;
      Serial.print("set pattern: ");
      Serial.println(gSeqPatternIndex);
    }
    gBtnTimeLast = millis();
  }
}
