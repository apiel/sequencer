# now

- need to improve freq selection
- need to improve freq env?
- sample improvement
- improve keyboard note on oscilation

- For the simple envelop we might just have a general level, attack time, substain time, realease time
    -> simple envelop might still have 4 phases, where attack level is 10-15% higher than substain level
    -> but for frequency envelop, we might have much more phase level and time
            --> the middle phases should a same starting and endpoint, so attack end and release start level should be the same.
            --> freq env, should start and stop at 127 instead of 0, so we can loop over on substain


# FIX

- remove noise on pattern screen

# previous

- Bug fix problem of not being able to change table
- Level per channel/phase

- Think of a way to control shift and envelop in 
  the same place for all the note?

    we could have mc1 mc2
       - mc1 is for adsr
       - mc2 for adsrFreq

Increase number of pattern

Plan pattern sequence
Plan phase setup sequence

Loop mode on phase

a way save and share and load phase&pattern 
   -> from a photo resistor? lifi
         https://github.com/egzola/ESP8266-ScreenSetWifi
   -> from screen with qr code sequence
            -> could use the photoresitor to switch QR code everytime flash goes away



when we increase bmp should we then increase adsr time?
