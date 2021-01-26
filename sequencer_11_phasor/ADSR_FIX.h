#ifndef ADSR_H_
#define ADSR_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Line.h"
#include "mozzi_fixmath.h"

enum { ATTACK, DECAY, SUSTAIN, RELEASE, IDLE };

template <unsigned int CONTROL_UPDATE_RATE, typename T = unsigned int>
class ADSR {
   private:
    unsigned int LERPS_PER_CONTROL;

    T update_step_counter;
    T num_update_steps;

    struct phase {
        unsigned int ms;
        byte phase_type;
        T update_steps;
        long lerp_steps;  // signed, to match params to transition (line) type
                          // Q15n16, below
        Q8n0 level;
    } attack, decay, sustain, release, idle;

    phase* current_phase;

    // Linear audio rate transitions for envelope
    // Line <unsigned long> transition;
    Line<Q15n16> transition;  // scale up unsigned char levels for better
                              // accuracy, then scale down again for output

    inline T convertMsecToControlUpdateSteps(unsigned int msec) {
        return (T)(((uint32_t)msec * CONTROL_UPDATE_RATE) >>
                   10);  // approximate /1000 with shift
    }

    inline void setPhase(phase* next_phase) {
        update_step_counter = 0;
        num_update_steps = next_phase->update_steps;
        transition.set(Q8n0_to_Q15n16(next_phase->level),
                       next_phase->lerp_steps);
        current_phase = next_phase;
    }

    inline void checkForAndSetNextPhase(phase* next_phase) {
        if (++update_step_counter >= num_update_steps) {
            setPhase(next_phase);
        }
    }

    inline void setTime(phase* p, unsigned int msec) {
        p->ms = msec;
        p->update_steps = convertMsecToControlUpdateSteps(msec);
        p->lerp_steps = (long)p->update_steps * LERPS_PER_CONTROL;
    }

    inline void setUpdateSteps(phase* p, unsigned int steps) {
        p->update_steps = steps;
        p->lerp_steps = (long)steps * LERPS_PER_CONTROL;
    }

   public:
    /** Constructor.
     */
    ADSR(unsigned int LERP_RATE) {
        attack.phase_type = ATTACK;
        decay.phase_type = DECAY;
        sustain.phase_type = SUSTAIN;
        release.phase_type = RELEASE;
        idle.phase_type = IDLE;
        release.level = 0;
        adsr_playing = false;
        current_phase = &idle;
        setLerpRate(LERP_RATE);
    }

    void setLerpRate(unsigned int LERP_RATE) {
        LERPS_PER_CONTROL = LERP_RATE / CONTROL_UPDATE_RATE;
        setTimes(attack.ms, decay.ms, sustain.ms, release.ms);
    }

    /** Updates the internal controls of the ADSR.
            Call this in updateControl().
            */
    void update() {  // control rate

        switch (current_phase->phase_type) {
            case ATTACK:
                if (decay.lerp_steps > 0) {
                    checkForAndSetNextPhase(&decay);
                    break;
                }
            case DECAY:
                if (sustain.lerp_steps > 0) {
                    checkForAndSetNextPhase(&sustain);
                    break;
                }

            case SUSTAIN:
                if (release.lerp_steps > 0) {
                    checkForAndSetNextPhase(&release);
                    break;
                }

            case RELEASE:
                checkForAndSetNextPhase(&idle);
                break;

            case IDLE:
                adsr_playing = false;
                break;
        }
    }

    /** Advances one audio step along the ADSR and returns the level.
    Call this in updateAudio().
    @return the next value, as an unsigned char.
     */
    inline unsigned char next() {
        unsigned char out = 0;
        if (adsr_playing) out = Q15n16_to_Q8n0(transition.next());
        return out;
    }

    /** Start the attack phase of the ADSR.  This will restart the ADSR no
    matter what phase it is up to.
    @param reset If true, the envelope will start from 0, even if it is still
    playing (often useful for effect envelopes). If false (default if omitted),
    the envelope will start rising from the current level, which could be
    non-zero, if it is still playing (most useful for note envelopes).
    */
    inline void noteOn(bool reset = false) {
        if (reset) transition.set(0);
        setPhase(&attack);

        if (attack.lerp_steps == 0) {
            if (decay.lerp_steps > 0)
                setPhase(&decay);
            else if (sustain.lerp_steps > 0)
                setPhase(&sustain);
            else if (release.lerp_steps > 0)
                setPhase(&release);
            else
                setPhase(&idle);
        }

        adsr_playing = true;
    }

    /** Start the release phase of the ADSR.
    @todo fix release for rate rather than steps (time), so it releases at the
    same rate whatever the current level.
    */
    inline void noteOff() { setPhase(&release); }

    /** Set the attack level of the ADSR.
    @param value the attack level.
     */
    inline void setAttackLevel(byte value) { attack.level = value; }

    /** Set the decay level of the ADSR.
    @param value the decay level.
    */
    inline void setDecayLevel(byte value) { decay.level = value; }

    /** Set the sustain level of the ADSR.
    @param value the sustain level.  Usually the same as the decay level,
    for a steady sustained note.
    */
    inline void setSustainLevel(byte value) { sustain.level = value; }

    /** Set the release level of the ADSR.  Normally you'd make this 0,
    but you have the option of some other value.
    @param value the release level (usually 0).
    */
    inline void setReleaseLevel(byte value) { release.level = value; }

    inline void setIdleLevel(byte value) { idle.level = value; }

    /** Set the attack and decay levels of the ADSR.  This assumes a
    conventional ADSR where the sustain continues at the same level as the
    decay, till the release ramps to 0.
    @param attack the new attack level.
    @param decay the new decay level.
    */
    inline void setADLevels(byte attack, byte decay) {
        setAttackLevel(attack);
        setDecayLevel(decay);
        setSustainLevel(decay);  // stay at decay level
        setReleaseLevel(1);
        setIdleLevel(0);
    }

    /** Set the attack, decay, sustain and release levels.
    @param attack the new attack level.
    @param decay the new sustain level.
    @param attack the new sustain level.
    @param decay the new release level.
    */
    inline void setLevels(byte attack, byte decay, byte sustain, byte release) {
        setAttackLevel(attack);
        setDecayLevel(decay);
        setSustainLevel(sustain);
        setReleaseLevel(release);
        setIdleLevel(0);
    }

    inline byte getLevel(byte phase_key) {
        if (phase_key == ATTACK) return attack.level;
        if (phase_key == DECAY) return decay.level;
        if (phase_key == SUSTAIN) return sustain.level;
        return release.level;
    }

    /** Set the attack time of the ADSR in milliseconds.
    The actual time taken will be resolved within the resolution of
    CONTROL_RATE.
    @param msec the unsigned int attack time in milliseconds.
    @note Beware of low values (less than 20 or so, depending on how many steps
    are being taken), in case internal step size gets calculated as 0, which
    would mean nothing happens.
     */
    inline void setAttackTime(unsigned int msec) { setTime(&attack, msec); }

    /** Set the decay time of the ADSR in milliseconds.
    The actual time taken will be resolved within the resolution of
    CONTROL_RATE.
    @param msec the unsigned int decay time in milliseconds.
    @note Beware of low values (less than 20 or so, depending on how many steps
    are being taken), in case internal step size gets calculated as 0, which
    would mean nothing happens.
    */
    inline void setDecayTime(unsigned int msec) { setTime(&decay, msec); }

    /** Set the sustain time of the ADSR in milliseconds.
    The actual time taken will be resolved within the resolution of
    CONTROL_RATE. The sustain phase will finish if the ADSR recieves a
    noteOff().
    @param msec the unsigned int sustain time in milliseconds.
    @note Beware of low values (less than 20 or so, depending on how many steps
    are being taken), in case internal step size gets calculated as 0, which
    would mean nothing happens.
    */
    inline void setSustainTime(unsigned int msec) { setTime(&sustain, msec); }

    /** Set the release time of the ADSR in milliseconds.
    The actual time taken will be resolved within the resolution of
    CONTROL_RATE.
    @param msec the unsigned int release time in milliseconds.
    @note Beware of low values (less than 20 or so, depending on how many steps
    are being taken), in case internal step size gets calculated as 0, which
    would mean nothing happens.
    */
    inline void setReleaseTime(unsigned int msec) { setTime(&release, msec); }

    inline void setIdleTime(unsigned int msec) { setTime(&idle, msec); }

    /** Set the attack, decay and release times of the ADSR in milliseconds.
    The actual times will be resolved within the resolution of CONTROL_RATE.
    @param attack_ms the new attack time in milliseconds.
    @param decay_ms the new decay time in milliseconds.
    @param sustain_ms the new sustain time in milliseconds.
    @param release_ms the new release time in milliseconds.
    @note Beware of low values (less than 20 or so, depending on how many steps
    are being taken), in case internal step size gets calculated as 0, which
    would mean nothing happens.
    */
    inline void setTimes(unsigned int attack_ms, unsigned int decay_ms,
                         unsigned int sustain_ms, unsigned int release_ms) {
        setAttackTime(attack_ms);
        setDecayTime(decay_ms);
        setSustainTime(sustain_ms);
        setReleaseTime(release_ms);
        setIdleTime(65535);  // guarantee step size of line will be 0
    }

    inline unsigned int getTime(byte phase_key) {
        if (phase_key == ATTACK) return attack.ms;
        if (phase_key == DECAY) return decay.ms;
        if (phase_key == SUSTAIN) return sustain.ms;
        return release.ms;
    }

    /** Set the attack time of the ADSR, expressed as the number of update steps
    (not ADSR::next() interpolation steps) in the attack phase.
    @param steps the number of times ADSR::update() will be called in the attack
    phase.
     */
    inline void setAttackUpdateSteps(unsigned int steps) {
        setUpdateSteps(&attack, steps);
    }

    /** Set the decay time of the ADSR, expressed as the number of update steps
    (not ADSR::next() interpolation steps) in the decay phase.
    @param steps the number of times ADSR::update() will be called in the decay
    phase.
     */
    inline void setDecayUpdateSteps(unsigned int steps) {
        setUpdateSteps(&decay, steps);
    }

    /** Set the sustain time of the ADSR, expressed as the number of update
    steps (not ADSR::next() interpolation steps) in the sustain phase.
    @param steps the number of times ADSR::update() will be called in the
    sustain phase.
    */
    inline void setSustainUpdateSteps(unsigned int steps) {
        setUpdateSteps(&sustain, steps);
    }

    /** Set the release time of the ADSR, expressed as the number of update
    steps (not ADSR::next() interpolation steps) in the release phase.
    @param steps the number of times ADSR::update() will be called in the
    release phase.
     */
    inline void setReleaseUpdateSteps(unsigned int steps) {
        setUpdateSteps(&release, steps);
    }

    inline void setIdleUpdateSteps(unsigned int steps) {
        setUpdateSteps(&idle, steps);
    }

    /** Set the attack, decay and release times of the ADSR, expressed in update
    steps (not ADSR::next() interpolation steps).
    @param attack_steps the number of update steps in the attack phase
    @param decay_steps the number of update steps in the decay phase
    @param sustain_steps the number of update steps in the sustain phase
    @param release_steps the number of update steps in the release phase
    */
    inline void setAllUpdateSteps(unsigned int attack_steps,
                                  unsigned int decay_steps,
                                  unsigned int sustain_steps,
                                  unsigned int release_steps) {
        setAttackUpdateSteps(attack_steps);
        setDecayUpdateSteps(decay_steps);
        setSustainUpdateSteps(sustain_steps);
        setReleaseUpdateSteps(release_steps);
        setIdleUpdateSteps(65535);  // guarantee step size of line will be 0
    }

    bool adsr_playing;

    /** Tells if the envelope is currently playing.
    @return true if playing, false if in IDLE state
    */
    inline bool playing() { return adsr_playing; }
};

/** @example 07.Envelopes/ADSR_Envelope/ADSR_Envelope.ino
This is an example of how to use the ADSR class.
*/

#endif /* ADSR_H_ */
