#pragma once

#include <SDTAnalysis.h>

#include "WrapperMacros.h"

namespace sdtwrappers {
    class Pitch {
    public:
        SDT_WRAP_STRUCT(Pitch)

        SDT_WRAP_PROPERTY(Pitch, Size, unsigned int)
        SDT_WRAP_PROPERTY(Pitch, Overlap, double)
        SDT_WRAP_PROPERTY(Pitch, Tolerance, double)

        SDT_WRAP_ANALYSIS_DSP(Pitch, 2)
    };

    class Myoelastic {
    public:
        SDT_WRAP_STRUCT(Myoelastic)

        SDT_WRAP_PROPERTY(Myoelastic, DcFrequency, double)
        SDT_WRAP_PROPERTY(Myoelastic, LowFrequency, double)
        SDT_WRAP_PROPERTY(Myoelastic, HighFrequency, double)
        SDT_WRAP_PROPERTY(Myoelastic, Threshold, double)

        void update() { SDTMyoelastic_update(ptr.get()); }

        SDT_WRAP_ANALYSIS_DSP(Myoelastic, 4)
    };

    class SpectralFeats {
    public:
        SDT_WRAP_STRUCT(SpectralFeats)

        SDT_WRAP_PROPERTY(SpectralFeats, MaxFreq, double)
        SDT_WRAP_PROPERTY(SpectralFeats, MinFreq, double)
        SDT_WRAP_PROPERTY(SpectralFeats, Overlap, double)
        SDT_WRAP_PROPERTY(SpectralFeats, Size, unsigned int)

        SDT_WRAP_ANALYSIS_DSP(SpectralFeats, 7)
    };

    class ZeroCrossing {
    public:
        SDT_WRAP_STRUCT(ZeroCrossing)

        SDT_WRAP_PROPERTY(ZeroCrossing, Overlap, double)
        SDT_WRAP_PROPERTY(ZeroCrossing, Size, unsigned int)

        SDT_WRAP_ANALYSIS_DSP(ZeroCrossing, 1)
    };
}