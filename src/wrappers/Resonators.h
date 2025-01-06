#pragma once

#include <SDTResonators.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class Resonator {
    public:
        SDT_WRAP_STRUCT(Resonator)

        double getPosition(const unsigned int pickup) { return SDTResonator_getPosition(ptr.get(), pickup); }
        void setPosition(const unsigned int pickup, const double f) { return SDTResonator_setPosition(ptr.get(), pickup, f); }

        double getVelocity(const unsigned int pickup) { return SDTResonator_getVelocity(ptr.get(), pickup); }
        void setVelocity(const unsigned int pickup, const double f) { return SDTResonator_setVelocity(ptr.get(), pickup, f); }

        double getFrequency(const unsigned int mode) { return SDTResonator_getFrequency(ptr.get(), mode); }
        void setFrequency(const unsigned int mode, const double f) { return SDTResonator_setFrequency(ptr.get(), mode, f); }

        double getDecay(const unsigned int mode) { return SDTResonator_getDecay(ptr.get(), mode); }
        void setDecay(const unsigned int mode, const double f) { return SDTResonator_setDecay(ptr.get(), mode, f); }

        double getWeight(const unsigned int mode) { return SDTResonator_getWeight(ptr.get(), mode); }
        void setWeight(const unsigned int mode, const double f) { return SDTResonator_setWeight(ptr.get(), mode, f); }

        double getGain(const unsigned int pickup, const unsigned int mode) { return SDTResonator_getGain(ptr.get(), pickup, mode); }
        void setGain(const unsigned int pickup, const unsigned int mode, const double f) { return SDTResonator_setGain(ptr.get(), pickup, mode, f); }

        SDT_WRAP_PROPERTY(Resonator, NPickups, int)
        SDT_WRAP_PROPERTY(Resonator, NModes, int)
        SDT_WRAP_PROPERTY(Resonator, ActiveModes, int)
        SDT_WRAP_PROPERTY(Resonator, FragmentSize, double)

        void applyForce(const unsigned int pickup, const double f) { SDTResonator_applyForce(ptr.get(), pickup, f); }
        double computeEnergy(const unsigned int pickup, const double f) { return SDTResonator_computeEnergy(ptr.get(), pickup, f); }

        void dsp() { SDTResonator_dsp(ptr.get()); }
    };
}