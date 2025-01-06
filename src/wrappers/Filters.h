#pragma once

#include <SDTFilters.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class AllPass {
    public:
        SDT_WRAP_STRUCT(AllPass)

        void setFeedback(const double f) { SDTAllPass_setFeedback(ptr.get(), f); }
        double dsp(const double in) { return SDTAllPass_dsp(ptr.get(), in); }
    };

    class Average {
    public:
        SDT_WRAP_STRUCT(Average)

        void setWindow(unsigned int i) { SDTAverage_setWindow(ptr.get(), i); }
        double dsp(const double in) { return SDTAverage_dsp(ptr.get(), in); }
    };

    class Biquad {
    public:
        SDT_WRAP_STRUCT(Biquad)

        void butterworthLP(const double fc) { SDTBiquad_butterworthLP(ptr.get(), fc); }
        void butterworthHP(const double fc) { SDTBiquad_butterworthHP(ptr.get(), fc); }
        void butterworthAP(const double fc) { SDTBiquad_butterworthAP(ptr.get(), fc); }

        void linkwitzRileyLP(const double fc) { SDTBiquad_linkwitzRileyLP(ptr.get(), fc); }
        void linkwitzRileyHP(const double fc) { SDTBiquad_linkwitzRileyHP(ptr.get(), fc); }

        double dsp(const double in) { return SDTBiquad_dsp(ptr.get(), in); }
    };

    class Comb {
    public:
        SDT_WRAP_STRUCT(Comb)

        long getMaxXDelay() const { return SDTComb_getMaxXDelay(ptr.get()); }
        long getMaxYDelay() const { return SDTComb_getMaxYDelay(ptr.get()); }

        void setXDelay(const double f) { SDTComb_setXDelay(ptr.get(), f); }
        void setYDelay(const double f) { SDTComb_setYDelay(ptr.get(), f); }
        void setXYDelay(const double f) { SDTComb_setXYDelay(ptr.get(), f); }

        void setXGain(const double f) { SDTComb_setXGain(ptr.get(), f); }
        void setYGain(const double f) { SDTComb_setYGain(ptr.get(), f); }
        void setXYGain(const double f) { SDTComb_setXYGain(ptr.get(), f); }

        double dsp(const double in) { return SDTComb_dsp(ptr.get(), in); }
    };

    class DCFilter {
    public:
        SDT_WRAP_STRUCT(DCFilter)

        SDT_WRAP_PROPERTY(DCFilter, Feedback, double)
        SDT_WRAP_PROPERTY(DCFilter, Frequency, double)

        double dsp(const double in) { return SDTDCFilter_dsp(ptr.get(), in); }
    };

    class Delay {
    public:
        SDT_WRAP_STRUCT(Delay)

        long getMaxDelay() const { return SDTDelay_getMaxDelay(ptr.get()); }
        SDT_WRAP_PROPERTY(Delay, Delay, double)

        void clear() { SDTDelay_clear(ptr.get()); }
        double dsp(const double in) { return SDTDelay_dsp(ptr.get(), in); }
    };

    class Envelope {
    public:
        SDT_WRAP_STRUCT(Envelope)

        SDT_WRAP_PROPERTY(Envelope, Attack, double)
        SDT_WRAP_PROPERTY(Envelope, Release, double)

        void update() { SDTEnvelope_update(ptr.get()); }
        double dsp(const double in) { return SDTEnvelope_dsp(ptr.get(), in); }
    };

    class OnePole {
    public:
        SDT_WRAP_STRUCT(OnePole)

        void setFeedback(const double f) { SDTOnePole_setFeedback(ptr.get(), f); }

        void lowpass(const double f) { SDTOnePole_lowpass(ptr.get(), f); }
        void highpass(const double f) { SDTOnePole_highpass(ptr.get(), f); }

        double dsp(const double in) { return SDTOnePole_dsp(ptr.get(), in); }
    };

    class TwoPoles {
    public:
        SDT_WRAP_STRUCT(TwoPoles)

        void lowpass(const double f) { SDTTwoPoles_lowpass(ptr.get(), f); }
        void highpass(const double f) { SDTTwoPoles_highpass(ptr.get(), f); }
        void resonant(const double f, const double q) { SDTTwoPoles_resonant(ptr.get(), f, q); }

        double dsp(const double in) { return SDTTwoPoles_dsp(ptr.get(), in); }
    };

    class Waveguide {
    public:
        SDT_WRAP_STRUCT(Waveguide)

        int getMaxDelay() const { return SDTWaveguide_getMaxDelay(ptr.get()); }
        SDT_WRAP_PROPERTY(Waveguide, Delay, double)
        SDT_WRAP_PROPERTY(Waveguide, FwdFeedback, double)
        SDT_WRAP_PROPERTY(Waveguide, RevFeedback, double)
        void setFwdDamping(const double f) { SDTWaveguide_setFwdDamping(ptr.get(), f); }
        void setRevDamping(const double f) { SDTWaveguide_setRevDamping(ptr.get(), f); }

        double getFwdOut() { return SDTWaveguide_getFwdOut(ptr.get()); }
        double getRevOut() { return SDTWaveguide_getRevOut(ptr.get()); }

        void dsp(const double fwdIn, const double revIn) { SDTWaveguide_dsp(ptr.get(), fwdIn, revIn); }
    };
}