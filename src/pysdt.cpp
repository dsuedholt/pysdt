#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/pair.h>

#include <SDT/SDTCommon.h>

#include "wrappers/Control.h"
#include "wrappers/Gases.h"
#include "wrappers/Interactors.h"
#include "wrappers/Liquids.h"
#include "wrappers/Resonators.h"

#include "BindingMacros.h"

namespace nb = nanobind;
using namespace nb::literals;

using arr1d = nb::ndarray<double, nb::ndim<1>>;

using namespace sdtwrappers;

void add_control_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("control");

    nb::class_<Bouncing>(m, "Bouncing")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(restitution, Bouncing, Restitution, double)
        .SDT_BIND_PROPERTY_RW(height, Bouncing, Height, double)
        .SDT_BIND_PROPERTY_RW(irregularity, Bouncing, Irregularity, double)
        .def("reset", &Bouncing::reset)
        .def("dsp", &Bouncing::dsp)
        .def("has_finished", &Bouncing::hasFinished);

    nb::class_<Breaking>(m, "Breaking")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(stored_energy, Breaking, StoredEnergy, double)
        .SDT_BIND_PROPERTY_RW(crushing_energy, Breaking, CrushingEnergy, double)
        .SDT_BIND_PROPERTY_RW(granularity, Breaking, Granularity, double)
        .SDT_BIND_PROPERTY_RW(fragmentation, Breaking, Fragmentation, double)
        .def("reset", &Breaking::reset)
        .def("dsp", &Breaking::dsp)
        .def("has_finished", &Breaking::hasFinished);

    nb::class_<Crumpling>(m, "Crumpling")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(crushing_energy, Crumpling, CrushingEnergy, double)
        .SDT_BIND_PROPERTY_RW(granularity, Crumpling, Granularity, double)
        .SDT_BIND_PROPERTY_RW(fragmentation, Crumpling, Fragmentation, double)
        .def("dsp", &Crumpling::dsp);

    nb::class_<Rolling>(m, "Rolling")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(energy, Rolling, Grain, double)
        .SDT_BIND_PROPERTY_RW(size, Rolling, Depth, double)
        .SDT_BIND_PROPERTY_RW(speed, Rolling, Mass, double)
        .SDT_BIND_PROPERTY_RW(speed, Rolling, Velocity, double)
        .def("dsp", &Rolling::dsp);

    nb::class_<Scraping>(m, "Scraping")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(energy, Scraping, Grain, double)
        .SDT_BIND_PROPERTY_RW(size, Scraping, Force, double)
        .SDT_BIND_PROPERTY_RW(speed, Scraping, Velocity, double)
        .def("dsp", &Scraping::dsp);
}

void add_common_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("common");

    m.attr("SDT_VERSION") = STRINGIFY(SDT_ver);
    m.attr("MACH1") = SDT_MACH1;
    m.attr("EARTH") = SDT_EARTH;
    m.attr("MICRO") = SDT_MICRO;
    m.attr("QUIET") = SDT_QUIET;

    m.def("blackman",
        [] (arr1d& sig) {
            SDT_blackman(sig.data(), static_cast<int>(sig.size()));
        });
    m.def("exp_rand", &SDT_expRand);
    m.def("gaussian_1d", &SDT_gaussian1D);
    m.def("gravity", &SDT_gravity);

    m.def("haar",
        [] (arr1d& sig) {
            SDT_haar(sig.data(), static_cast<int>(sig.size()));
        });

    m.def("hanning",
        [] (arr1d& sig) {
            SDT_hanning(sig.data(), static_cast<int>(sig.size()));
        });

    m.def("ihaar",
        [] (arr1d& sig) {
            SDT_ihaar(sig.data(), static_cast<int>(sig.size()));
        });

    m.def("kinetic", &SDT_kinetic);
    m.def("samples_in_air", &SDT_samplesInAir);
    m.def("samples_in_air_inv", &SDT_samplesInAir_inv);
    m.def("set_samplerate", &SDT_setSampleRate);

    m.def("sinc",
        [] (arr1d& sig, double f) {
            SDT_sinc(sig.data(), f, static_cast<int>(sig.size()));
        });

    m.def("true_peak_pos",
        [] (arr1d& sig, int peak) {
            return SDT_truePeakPos(sig.data(), peak);
        });

    m.def("true_peak_value",
        [] (arr1d& sig, int peak) {
            return SDT_truePeakValue(sig.data(), peak);
        });

    m.def("wrap", &SDT_wrap);

    m.def("get_samplerate",
        [] () { return SDT_sampleRate; }
    );

    m.def("get_timestep",
        [] () { return SDT_timeStep; }
    );
}

void add_gases_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("gases");

    nb::class_<Explosion>(m, "Explosion")
        .def(nb::init<long, long>())
        .SDT_BIND_PROPERTY_RW(max_scatter, Explosion, MaxScatter, double)
        .SDT_BIND_PROPERTY_RW(max_delay, Explosion, MaxDelay, double)
        .SDT_BIND_PROPERTY_RW(blast_time, Explosion, BlastTime, double)
        .SDT_BIND_PROPERTY_RW(scatter_time, Explosion, ScatterTime, double)
        .SDT_BIND_PROPERTY_RW(dispersion, Explosion, Dispersion, double)
        .SDT_BIND_PROPERTY_RW(distance, Explosion, Distance, double)
        .SDT_BIND_PROPERTY_RW(wave_speed, Explosion, WaveSpeed, double)
        .SDT_BIND_PROPERTY_RW(wind_speed, Explosion, WindSpeed, double)
        .def("trigger", &Explosion::trigger)
        .def("dsp", &Explosion::dsp);

    nb::class_<WindKarman>(m, "WindKarman")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(diameter, WindKarman, Diameter, double)
        .SDT_BIND_PROPERTY_RW(wind_speed, WindKarman, WindSpeed, double)
        .def("dsp", &WindKarman::dsp);

    nb::class_<WindFlow>(m, "WindFlow")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(wind_speed, WindFlow, WindSpeed, double)
        .def("update", &WindFlow::update)
        .def("dsp", &WindFlow::dsp);

    nb::class_<WindCavity>(m, "WindCavity")
        .def(nb::init<int>())
        .SDT_BIND_PROPERTY_RW(max_delay, WindCavity, MaxDelay, double)
        .SDT_BIND_PROPERTY_RW(length, WindCavity, Length, double)
        .SDT_BIND_PROPERTY_RW(diameter, WindCavity, Diameter, double)
        .SDT_BIND_PROPERTY_RW(wind_speed, WindCavity, WindSpeed, double)
        .def("dsp", &WindCavity::dsp);
}

void add_interactors_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("interactors");

    nb::class_<Interactor>(m, "Interactor")
        .SDT_BIND_PROPERTY_RW(first_resonator, Interactor, FirstResonator, std::shared_ptr<Resonator>)
        .SDT_BIND_PROPERTY_RW(second_resonator, Interactor, SecondResonator, std::shared_ptr<Resonator>)
        .SDT_BIND_PROPERTY_RW(first_point, Interactor, FirstPoint, long)
        .SDT_BIND_PROPERTY_RW(second_point, Interactor, SecondPoint, long)
        .def("compute_force", &Interactor::computeForce)
        .def("dsp", &Interactor::dsp);

    nb::class_<Impact, Interactor>(m, "Impact")
        .def(nb::init<>())
        .SDT_BIND_PROPERTY_RW(stiffness, Impact, Stiffness, double)
        .SDT_BIND_PROPERTY_RW(dissipation, Impact, Dissipation, double)
        .SDT_BIND_PROPERTY_RW(shape, Impact, Shape, double);
}

void add_liquids_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("liquids");

    nb::class_<Bubble>(m, "Bubble")
      .def(nb::init<>())
      .SDT_BIND_PROPERTY_RW(radius, Bubble, Radius, double)
      .SDT_BIND_PROPERTY_RW(rise_factor, Bubble, RiseFactor, double)
      .SDT_BIND_PROPERTY_RW(depth, Bubble, Depth, double)
      .def("dsp", &Bubble::dsp)
      .def("norm_amp", &Bubble::normAmp)
      .def("trigger", &Bubble::trigger);

    nb::class_<FluidFlow>(m, "FluidFlow")
        .def(nb::init<int>())
        .SDT_BIND_PROPERTY_RW(n_bubbles, FluidFlow, NBubbles, int)
        .SDT_BIND_PROPERTY_RW(min_radius, FluidFlow, MinRadius, double)
        .SDT_BIND_PROPERTY_RW(max_radius, FluidFlow, MaxRadius, double)
        .SDT_BIND_PROPERTY_RW(exp_radius, FluidFlow, ExpRadius, double)
        .SDT_BIND_PROPERTY_RW(min_depth, FluidFlow, MinDepth, double)
        .SDT_BIND_PROPERTY_RW(max_depth, FluidFlow, MaxDepth, double)
        .SDT_BIND_PROPERTY_RW(exp_depth, FluidFlow, ExpDepth, double)
        .SDT_BIND_PROPERTY_RW(rise_factor, FluidFlow, RiseFactor, double)
        .SDT_BIND_PROPERTY_RW(rise_cutoff, FluidFlow, RiseCutoff, double)
        .SDT_BIND_PROPERTY_RW(avg_rate, FluidFlow, AvgRate, double)
        .def("dsp", &FluidFlow::dsp);
}

void add_resonators_submodule(nb::module_& root) {
    nb::module_ m = root.def_submodule("resonators");

    nb::class_<Resonator>(m, "Resonator")
        .def(nb::init<int, int>())
        .def("get_position", &Resonator::getPosition)
        .def("set_position", &Resonator::setPosition)
        .def("get_velocity", &Resonator::getVelocity)
        .def("set_velocity", &Resonator::setVelocity)
        .def("get_frequency", &Resonator::getFrequency)
        .def("set_frequency", &Resonator::setFrequency)
        .def("get_decay", &Resonator::getDecay)
        .def("set_decay", &Resonator::setDecay)
        .def("get_weight", &Resonator::getWeight)
        .def("set_weight", &Resonator::setWeight)
        .def("get_gain", &Resonator::getGain)
        .def("set_gain", &Resonator::setGain)
        .SDT_BIND_PROPERTY_RW(n_pickups, Resonator, NPickups, int)
        .SDT_BIND_PROPERTY_RW(n_modes, Resonator, NModes, int)
        .SDT_BIND_PROPERTY_RW(active_modes, Resonator, ActiveModes, int)
        .SDT_BIND_PROPERTY_RW(fragment_size, Resonator, FragmentSize, double)
        .def("apply_force", &Resonator::applyForce)
        .def("compute_energy", &Resonator::computeEnergy)
        .def("dsp", &Resonator::dsp);
}

NB_MODULE(pysdt, m) {
    add_control_submodule(m);
    add_common_submodule(m);
    add_gases_submodule(m);
    add_interactors_submodule(m);
    add_liquids_submodule(m);
    add_resonators_submodule(m);
}