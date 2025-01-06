#pragma once

#include <SDTDCMotor.h>
#include "WrapperMacros.h"

namespace sdtwrappers {
    class DCMotor {
        SDT_WRAP_STRUCT(DCMotor)

        SDT_WRAP_PROPERTY(DCMotor, MaxSize, long)
        SDT_WRAP_PROPERTY(DCMotor, Rpm, double)
        SDT_WRAP_PROPERTY(DCMotor, Load, double)
        SDT_WRAP_PROPERTY(DCMotor, Coils, long)
        SDT_WRAP_PROPERTY(DCMotor, Size, double)
        SDT_WRAP_PROPERTY(DCMotor, Reson, double)
        SDT_WRAP_PROPERTY(DCMotor, GearRatio, double)
        SDT_WRAP_PROPERTY(DCMotor, Harshness, double)
        SDT_WRAP_PROPERTY(DCMotor, RotorGain, double)
        SDT_WRAP_PROPERTY(DCMotor, GearGain, double)
        SDT_WRAP_PROPERTY(DCMotor, BrushGain, double)
        SDT_WRAP_PROPERTY(DCMotor, AirGain, double)

        void update() { SDTDCMotor_update(ptr.get()); }
        double dsp() { return SDTDCMotor_dsp(ptr.get()); }
    };
}