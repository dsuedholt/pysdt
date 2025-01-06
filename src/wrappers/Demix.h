#pragma once

#include <SDTDemix.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class Demix {
    public:
        SDT_WRAP_STRUCT(Demix)

        SDT_WRAP_PROPERTY(Demix, Size, int)
        SDT_WRAP_PROPERTY(Demix, Radius, int)
        SDT_WRAP_PROPERTY(Demix, Overlap, double)
        SDT_WRAP_PROPERTY(Demix, NoiseThreshold, double)
        SDT_WRAP_PROPERTY(Demix, TonalThreshold, double)

        SDT_WRAP_DSP_MANY_OUT_WITH_INPUT(Demix, 3)
    };
}