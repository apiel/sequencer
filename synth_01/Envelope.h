#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Line.h"
#include "mozzi_fixmath.h"

template <unsigned int CONTROL_UPDATE_RATE, byte NUM_PHASES = 2>
class Envelope {
   private:
    unsigned int LERPS_PER_CONTROL;
    unsigned int LERP_RATE;

    unsigned int update_step_counter;
    unsigned int num_update_steps;

    byte loop_start = NUM_PHASES;
    byte loop_stop = NUM_PHASES;

    struct phase {
        unsigned int ms;
        byte phase_type;
        unsigned int update_steps;
        long lerp_steps;  // signed, to match params to transition (line) type
                          // Q15n16, below
        Q8n0 level;
    };

    byte current = NUM_PHASES;  // NUM_PHASES = off
    phase phases[NUM_PHASES];

    // Linear audio rate transitions for envelope
    // Line <unsigned long> transition;
    Line<Q15n16> transition;  // scale up unsigned char levels for better
                              // accuracy, then scale down again for output

    inline unsigned int convertMsecToControlUpdateSteps(unsigned int msec) {
        return (unsigned int)(((uint32_t)msec * CONTROL_UPDATE_RATE) >>
                              10);  // approximate /1000 with shift
    }

    inline void setNextPhase() {
        // ToDo: looooop fix bug if loop doesnt have length...
        if (loop_start < NUM_PHASES && loop_stop < NUM_PHASES &&
            current == loop_stop) {
            setNextPhase(loop_start);
        } else {
            setNextPhase(current + 1);
        }
    }
    inline void setNextPhase(byte index) {
        update_step_counter = 0;
        current = index;
        if (playing()) {
            if (phases[current].lerp_steps == 0) {
                setNextPhase();
            } else {
                num_update_steps = phases[current].update_steps;
                transition.set(current == 0
                                   ? 0
                                   : Q8n0_to_Q15n16(phases[current - 1].level));
                transition.set(Q8n0_to_Q15n16(phases[current].level),
                               phases[current].lerp_steps);
            }
        }
    }

    inline void setUpdateSteps(phase* p, unsigned int steps) {
        p->update_steps = steps;
        p->lerp_steps = (long)steps * LERPS_PER_CONTROL;
    }

    bool isValidIndex(byte index) { return index < NUM_PHASES; }

   public:
    Envelope(unsigned int lerp_rate) { setLerpRate(lerp_rate); }

    void setLerpRate(unsigned int lerp_rate) {
        LERP_RATE = lerp_rate;
        LERPS_PER_CONTROL = LERP_RATE / CONTROL_UPDATE_RATE;
        for (byte i = 0; i < NUM_PHASES; i++) {
            setTime(i, phases[i].ms);
        }
    }

    inline void set(byte index, unsigned int msec, byte value) {
        setTime(index, msec);
        setLevel(index, value);
    }

    inline void setTime(byte index, unsigned int msec) {
        if (isValidIndex(index)) {
            phases[index].ms = msec;
            phases[index].update_steps = convertMsecToControlUpdateSteps(msec);
            phases[index].lerp_steps =
                (long)phases[index].update_steps * LERPS_PER_CONTROL;
        }
    }

    inline unsigned int getTime(byte index) {
        if (isValidIndex(index)) {
            return phases[index].ms;
        }
        return 0;
    }

    inline void setLevel(byte index, byte value) {
        if (isValidIndex(index)) {
            // seem that when we have level to 0, there is a little noize
            // phases[index].level = max(value, 1);
            phases[index].level = value;
        }
    }

    inline byte getLevel(byte index) {
        if (isValidIndex(index)) {
            return phases[index].level;
        }
        return 0;
    }

    unsigned int getLerpRate() { return LERP_RATE; }

    void update() {
        if (playing() && ++update_step_counter >= num_update_steps) {
            setNextPhase();
        }
    }

    inline unsigned char next() {
        unsigned char out = 0;
        if (playing()) out = Q15n16_to_Q8n0(transition.next());
        return out;
    }

    inline void play() { play(0); }
    inline void play(byte index) {
        if (isValidIndex(index)) {
            setNextPhase(index);
        }
    }

    inline void stop(byte index) {
        stop();
        setNextPhase(index);
    }

    inline void stop() {
        loop_start = NUM_PHASES;
        loop_stop = NUM_PHASES;
    }

    inline void loop(byte start) { loop(start, start); }

    inline void loop(byte start, byte stop) {
        loop_start = start;
        loop_stop = stop;
    }

    inline bool playing() { return current < NUM_PHASES; }
};

#endif
