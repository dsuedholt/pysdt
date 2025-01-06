#pragma once

#include <SDTMotor.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class Motor {
    public:
        SDT_WRAP_STRUCT(Motor)

        // getRpm is declared, but not defined in the SDT library. so only have a setter
        void setRpm(const double f) { SDTMotor_setRpm(ptr.get(), f); }

        SDT_WRAP_PROPERTY(Motor, MaxDelay, long)
        SDT_WRAP_PROPERTY(Motor, Cycle, double)
        SDT_WRAP_PROPERTY(Motor, Throttle, double)
        SDT_WRAP_PROPERTY(Motor, NCylinders, int)
        SDT_WRAP_PROPERTY(Motor, CylinderSize, double)
        SDT_WRAP_PROPERTY(Motor, CompressionRatio, double)
        SDT_WRAP_PROPERTY(Motor, SparkTime, double)
        SDT_WRAP_PROPERTY(Motor, Asymmetry, double)
        SDT_WRAP_PROPERTY(Motor, Backfire, double)
        SDT_WRAP_PROPERTY(Motor, IntakeSize, double)
        SDT_WRAP_PROPERTY(Motor, ExtractorSize, double)
        SDT_WRAP_PROPERTY(Motor, ExhaustSize, double)
        SDT_WRAP_PROPERTY(Motor, Expansion, double)
        SDT_WRAP_PROPERTY(Motor, MufflerSize, double)
        SDT_WRAP_PROPERTY(Motor, MufflerFeedback, double)
        SDT_WRAP_PROPERTY(Motor, OutletSize, double)
        SDT_WRAP_PROPERTY(Motor, Damp, double)
        SDT_WRAP_PROPERTY(Motor, Dc, double)

        void setTwoStroke() { SDTMotor_setTwoStroke(ptr.get()); }
        void setFourStroke() { SDTMotor_setFourStroke(ptr.get()); }

        void update() { SDTMotor_update(ptr.get()); }
        SDT_WRAP_DSP_MANY_OUT_WITHOUT_INPUT(Motor, 3)
    };
}