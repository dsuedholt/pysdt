#pragma once

#include <SDTLiquids.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class Bubble {
    public:
        SDT_WRAP_STRUCT(Bubble)

        SDT_WRAP_PROPERTY(Bubble, Radius, double)
        SDT_WRAP_PROPERTY(Bubble, RiseFactor, double)
        SDT_WRAP_PROPERTY(Bubble, Depth, double)

        void trigger() { SDTBubble_trigger(ptr.get()); }
        void normAmp() { SDTBubble_normAmp(ptr.get()); }

        void dsp() { SDTBubble_dsp(ptr.get()); }
    };

    class FluidFlow {
    public:
        SDT_WRAP_STRUCT(FluidFlow)

        SDT_WRAP_PROPERTY(FluidFlow, NBubbles, int)
        SDT_WRAP_PROPERTY(FluidFlow, MinRadius, double)
        SDT_WRAP_PROPERTY(FluidFlow, MaxRadius, double)
        SDT_WRAP_PROPERTY(FluidFlow, ExpRadius, double)
        SDT_WRAP_PROPERTY(FluidFlow, MinDepth, double)
        SDT_WRAP_PROPERTY(FluidFlow, MaxDepth, double)
        SDT_WRAP_PROPERTY(FluidFlow, ExpDepth, double)
        SDT_WRAP_PROPERTY(FluidFlow, RiseFactor, double)
        SDT_WRAP_PROPERTY(FluidFlow, RiseCutoff, double)
        SDT_WRAP_PROPERTY(FluidFlow, AvgRate, double)

        void dsp() { SDTFluidFlow_dsp(ptr.get()); }
    };
}