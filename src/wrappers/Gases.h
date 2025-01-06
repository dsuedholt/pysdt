#pragma once

#include <SDTGases.h>

#include "WrapperMacros.h"

namespace sdtwrappers {
    class Explosion {
    public:
        SDT_WRAP_STRUCT(Explosion)

        SDT_WRAP_PROPERTY(Explosion, MaxScatter, double)
        SDT_WRAP_PROPERTY(Explosion, MaxDelay, double)
        SDT_WRAP_PROPERTY(Explosion, BlastTime, double)
        SDT_WRAP_PROPERTY(Explosion, ScatterTime, double)
        SDT_WRAP_PROPERTY(Explosion, Dispersion, double)
        SDT_WRAP_PROPERTY(Explosion, Distance, double)
        SDT_WRAP_PROPERTY(Explosion, WaveSpeed, double)
        SDT_WRAP_PROPERTY(Explosion, WindSpeed, double)

        void trigger() { SDTExplosion_trigger(ptr.get()); }

        SDT_WRAP_DSP_MANY_OUT_WITHOUT_INPUT(Explosion, 2)
    };

    class WindKarman {
    public:
        SDT_WRAP_STRUCT(WindKarman)

        SDT_WRAP_PROPERTY(WindKarman, Diameter, double)
        SDT_WRAP_PROPERTY(WindKarman, WindSpeed, double)

        double dsp() { return SDTWindKarman_dsp(ptr.get()); }
    };

    class WindFlow {
    public:
        SDT_WRAP_STRUCT(WindFlow)

        SDT_WRAP_PROPERTY(WindFlow, WindSpeed, double)

        void update() { SDTWindFlow_update(ptr.get()); }
        double dsp() { return SDTWindFlow_dsp(ptr.get()); }
    };

    class WindCavity {
    public:
        SDT_WRAP_STRUCT(WindCavity)

        SDT_WRAP_PROPERTY(WindCavity, MaxDelay, double)
        SDT_WRAP_PROPERTY(WindCavity, Length, double)
        SDT_WRAP_PROPERTY(WindCavity, Diameter, double)
        SDT_WRAP_PROPERTY(WindCavity, WindSpeed, double)

        double dsp() { return SDTWindCavity_dsp(ptr.get()); }
    };
}