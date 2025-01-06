#pragma once

#include <vector>

#include <SDTInteractors.h>

#include "Resonators.h"
#include "WrapperMacros.h"

namespace sdtwrappers {
    class Interactor {
    public:
        Interactor() = delete;

        void setFirstResonator(std::shared_ptr<Resonator> resonator) {
            res0 = std::move(resonator);
            SDTInteractor_setFirstResonator(ptr.get(), res0->getRawPointer());
            updateOutsSize();
        }

        std::shared_ptr<Resonator> getFirstResonator() { return res0; }

        void setSecondResonator(std::shared_ptr<Resonator> resonator) {
            res1 = std::move(resonator);
            SDTInteractor_setSecondResonator(ptr.get(), res1->getRawPointer());
            updateOutsSize();
        }

        std::shared_ptr<Resonator> getSecondResonator() { return res1; }

        SDT_WRAP_PROPERTY(Interactor, FirstPoint, long)
        SDT_WRAP_PROPERTY(Interactor, SecondPoint, long)

        double computeForce() { return SDTInteractor_computeForce(ptr.get()); }

        void dsp(double f0, double v0, double s0, double f1, double v1, double s1) {
            SDTInteractor_dsp(ptr.get(), f0, v0, s0, f1, v1, s1, outs.data());
        }

    protected:
        typedef void (*Deleter)(SDTInteractor*);
        std::unique_ptr<SDTInteractor, Deleter> ptr;

        Interactor(SDTInteractor* p, Deleter del) : ptr(std::unique_ptr<SDTInteractor, Deleter>(p, del)) {}

    private:
        std::vector<double> outs;
        std::shared_ptr<Resonator> res0, res1;

        void updateOutsSize() {
            int newSize = 0;
            if (res0) newSize += res0->getNPickups();
            if (res1) newSize += res1->getNPickups();
            outs.resize(newSize);
        }
    };

    class Impact : public Interactor {
    public:
        Impact() : Interactor(SDTImpact_new(), &SDTImpact_free) {}

        SDT_WRAP_PROPERTY(Impact, Stiffness, double)
        SDT_WRAP_PROPERTY(Impact, Dissipation, double)
        SDT_WRAP_PROPERTY(Impact, Shape, double)
    };

    class Friction : public Interactor {
    public:
        Friction() : Interactor(SDTFriction_new(), &SDTFriction_free) {}

        SDT_WRAP_PROPERTY(Friction, NormalForce, double)
        SDT_WRAP_PROPERTY(Friction, StribeckVelocity, double)
        SDT_WRAP_PROPERTY(Friction, StaticCoefficient, double)
        SDT_WRAP_PROPERTY(Friction, DynamicCoefficient, double)
        SDT_WRAP_PROPERTY(Friction, BreakAway, double)
        SDT_WRAP_PROPERTY(Friction, Stiffness, double)
        SDT_WRAP_PROPERTY(Friction, Dissipation, double)
        SDT_WRAP_PROPERTY(Friction, Viscosity, double)
        SDT_WRAP_PROPERTY(Friction, Noisiness, double)
    };
}