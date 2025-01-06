#pragma once

#include <utility>

#include <SDT/SDTControl.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class Bouncing {
    public:
        SDT_WRAP_STRUCT(Bouncing)

        SDT_WRAP_PROPERTY(Bouncing, Restitution, double)
        SDT_WRAP_PROPERTY(Bouncing, Height, double)
        SDT_WRAP_PROPERTY(Bouncing, Irregularity, double)

        void reset() { SDTBouncing_reset(ptr.get()); }
        double dsp() { return SDTBouncing_dsp(ptr.get()); }
        bool hasFinished() { return SDTBouncing_hasFinished(ptr.get()); }
    };

    class Breaking {
    public:
        SDT_WRAP_STRUCT(Breaking)

        SDT_WRAP_PROPERTY(Breaking, StoredEnergy, double)
        SDT_WRAP_PROPERTY(Breaking, CrushingEnergy, double)
        SDT_WRAP_PROPERTY(Breaking, Granularity, double)
        SDT_WRAP_PROPERTY(Breaking, Fragmentation, double)

        void reset() { SDTBreaking_reset(ptr.get()); }

        std::pair<double, double> dsp() {
            SDTBreaking_dsp(ptr.get(), dspOuts);
            return {dspOuts[0], dspOuts[1]};
        }

        bool hasFinished() { return SDTBreaking_hasFinished(ptr.get()); }

    private:
        double dspOuts[2] = {0, 0};
    };

    class Crumpling {
    public:
        SDT_WRAP_STRUCT(Crumpling)

        SDT_WRAP_PROPERTY(Crumpling, CrushingEnergy, double)
        SDT_WRAP_PROPERTY(Crumpling, Granularity, double)
        SDT_WRAP_PROPERTY(Crumpling, Fragmentation, double)

        std::pair<double, double> dsp() {
            SDTCrumpling_dsp(ptr.get(), dspOuts);
            return {dspOuts[0], dspOuts[1]};
        }

    private:
        double dspOuts[2] = {0, 0};
    };

    class Rolling {
    public:
        SDT_WRAP_STRUCT(Rolling)

        SDT_WRAP_PROPERTY(Rolling, Grain, double)
        SDT_WRAP_PROPERTY(Rolling, Depth, double)
        SDT_WRAP_PROPERTY(Rolling, Mass, double)
        SDT_WRAP_PROPERTY(Rolling, Velocity, double)

        double dsp(const double f) { return SDTRolling_dsp(ptr.get(), f); }
    };

    class Scraping {
    public:
        SDT_WRAP_STRUCT(Scraping)

        SDT_WRAP_PROPERTY(Scraping, Grain, double)
        SDT_WRAP_PROPERTY(Scraping, Force, double)
        SDT_WRAP_PROPERTY(Scraping, Velocity, double)

        double dsp(const double f) { return SDTScraping_dsp(ptr.get(), f); }
    };
}