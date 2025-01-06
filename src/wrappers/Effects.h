#pragma once

#include <SDTEffects.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class PitchShift {
        SDT_WRAP_STRUCT(PitchShift)

        SDT_WRAP_PROPERTY(PitchShift, Size, int)
        SDT_WRAP_PROPERTY(PitchShift, Oversample, int)
        SDT_WRAP_PROPERTY(PitchShift, Ratio, double)
        SDT_WRAP_PROPERTY(PitchShift, Overlap, double)

        double dsp(const double in) { return SDTPitchShift_dsp(ptr.get(), in); }
    };

    class Reverb {
        SDT_WRAP_STRUCT(Reverb)

        SDT_WRAP_PROPERTY(Reverb, MaxDelay, long)
        SDT_WRAP_PROPERTY(Reverb, XSize, double)
        SDT_WRAP_PROPERTY(Reverb, YSize, double)
        SDT_WRAP_PROPERTY(Reverb, ZSize, double)
        SDT_WRAP_PROPERTY(Reverb, Randomness, double)
        SDT_WRAP_PROPERTY(Reverb, Time, double)
        SDT_WRAP_PROPERTY(Reverb, Time1k, double)

        void update() { SDTReverb_update(ptr.get()); }
        double dsp(const double in) { return SDTReverb_dsp(ptr.get(), in); }
    };
}