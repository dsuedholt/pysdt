#pragma once

#include <SDTOscillators.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class PinkNoise {
    public:
        SDT_WRAP_STRUCT(PinkNoise)
        double dsp() { return SDTPinkNoise_dsp(ptr.get()); }
    };

    double whiteNoise() { return SDT_whiteNoise(); }
}