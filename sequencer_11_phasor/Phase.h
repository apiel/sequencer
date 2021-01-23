#ifndef PHASE_H_
#define PHASE_H_

#include "ADSR_FIX.h"

class Phase {
   public:
    Phase() {}

   private:
    ADSR<CONTROL_RATE, AUDIO_RATE> adsr;
    ADSR<CONTROL_RATE, AUDIO_RATE> adsrFreq;
    // Oscil<MAX_NUM_CELLS, AUDIO_RATE> oscil;
};

#endif
