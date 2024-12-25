#pragma once

#include <SDT/SDTLiquids.h>
#include "Macros.h"

class Bubble {
public:
    SDT_WRAP_STRUCT(Bubble)

    SDT_WRAP_PROPERTY(Bubble, Radius, double)
    SDT_WRAP_PROPERTY(Bubble, RiseFactor, double)
    SDT_WRAP_PROPERTY(Bubble, Depth, double)

    void trigger() { SDTBubble_trigger(ptr); }
    void normAmp() { SDTBubble_normAmp(ptr); }

    SDT_WRAP_DSP(Bubble)
};

class FluidFlow {
public:
    SDT_WRAP_STRUCT_WITH_ONE_ARG(FluidFlow, int)

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

    SDT_WRAP_DSP(FluidFlow)
};