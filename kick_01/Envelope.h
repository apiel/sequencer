#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
// #include <EventDelay.h>

#include "Line.h"
#include "mozzi_fixmath.h"

template <unsigned int CONTROL_UPDATE_RATE, byte NUM_PHASES = 2,
          byte START_LEVEL = 0>
class Envelope {
   private:
    unsigned int LERPS_PER_CONTROL;
    unsigned int LERP_RATE;

    unsigned int update_step_counter;
    unsigned int num_update_steps;

    byte stop_index = NUM_PHASES;
    unsigned char stop_level = 0;

    bool isLooping = false;
    byte loopCounter = 0;

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

    inline void setNextPhase() { setNextPhase(current + 1); }
    inline void setNextPhase(byte index) {
        update_step_counter = 0;
        current = index;
        if (playing()) {
            if (phases[current].lerp_steps == 0) {
                setNextPhase();
            } else {
                num_update_steps = phases[current].update_steps;
                transition.set(current == 0
                                   ? Q8n0_to_Q15n16(START_LEVEL)
                                   : Q8n0_to_Q15n16(phases[current - 1].level),
                               Q8n0_to_Q15n16(phases[current].level),
                               phases[current].lerp_steps);
            }
        } else if (isLooping) {
            setNextPhase(0);
        } else if (loopCounter) {
            loopCounter--;
            setNextPhase(0);
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

    unsigned int getTotalTime() {
        unsigned int ms = 0;
        for (byte i = 0; i < NUM_PHASES; i++) {
            ms += phases[i].ms;
        }
        return ms;
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
        if (playing()) {
            Q15n16 level = transition.next();
            // There might be a better way to solve this
            // transition.next() can return negative value
            // so -123 will be transform to 255 and therefor make a noize
            // when next is called before update_step_counter
            // maybe line should a target value or target step and not exceed it
            // return Q15n16_to_Q8n0(level);
            return level > 0 ? Q15n16_to_Q8n0(level) : 0;
        }
        // return 0;
        return stop_level;
    }

    inline void play() { play(0); }
    inline void play(byte start_index) { play(start_index, NUM_PHASES); }
    inline void play(byte start_index, byte end_index) {
        if (isValidIndex(start_index)) {
            stop_index = end_index;
            stop_level = phases[stop_index - 1].level;
            setNextPhase(start_index);
        }
    }

    inline void loop() { isLooping = true; }
    inline void stopLoop() {
        isLooping = false;
        loopCounter = 0;
    }
    inline void loop(byte count) { loopCounter = count; }

    inline bool playing() { return current < stop_index; }
};

#endif
