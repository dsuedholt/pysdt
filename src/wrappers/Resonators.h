#pragma once

#include <SDT/SDTResonators.h>
#include "Macros.h"

class Resonator {
public:
    SDT_WRAP_STRUCT_WITH_TWO_ARGS(Resonator, int, int)

    double getPosition(const unsigned int pickup) { return SDTResonator_getPosition(ptr, pickup); }
    void setPosition(const unsigned int pickup, const double f) { return SDTResonator_setPosition(ptr, pickup, f); }

    double getVelocity(const unsigned int pickup) { return SDTResonator_getVelocity(ptr, pickup); }
    void setVelocity(const unsigned int pickup, const double f) { return SDTResonator_setVelocity(ptr, pickup, f); }

    double getFrequency(const unsigned int mode) { return SDTResonator_getFrequency(ptr, mode); }
    void setFrequency(const unsigned int mode, const double f) { return SDTResonator_setFrequency(ptr, mode, f); }

    double getDecay(const unsigned int mode) { return SDTResonator_getDecay(ptr, mode); }
    void setDecay(const unsigned int mode, const double f) { return SDTResonator_setDecay(ptr, mode, f); }

    double getWeight(const unsigned int mode) { return SDTResonator_getWeight(ptr, mode); }
    void setWeight(const unsigned int mode, const double f) { return SDTResonator_setWeight(ptr, mode, f); }

    double getGain(const unsigned int pickup, const unsigned int mode) { return SDTResonator_getGain(ptr, pickup, mode); }
    void setGain(const unsigned int pickup, const unsigned int mode, const double f) { return SDTResonator_setGain(ptr, pickup, mode, f); }

    SDT_WRAP_PROPERTY(Resonator, NPickups, int)
    SDT_WRAP_PROPERTY(Resonator, NModes, int)
    SDT_WRAP_PROPERTY(Resonator, ActiveModes, int)
    SDT_WRAP_PROPERTY(Resonator, FragmentSize, double)

    void applyForce(const unsigned int pickup, const double f) { SDTResonator_applyForce(ptr, pickup, f); }
    double computeEnergy(const unsigned int pickup, const double f) { return SDTResonator_computeEnergy(ptr, pickup, f); }

    void dsp() { SDTResonator_dsp(ptr); }
};