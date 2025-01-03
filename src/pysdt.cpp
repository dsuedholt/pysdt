#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>

#include <SDT/SDTCommon.h>

#include "wrappers/Liquids.h"
#include "wrappers/Resonators.h"

#include "BindingMacros.h"

namespace nb = nanobind;
using namespace nb::literals;

using arr1d = nb::ndarray<double, nb::ndim<1>>;

void add_common_submodule(nb::module_ &root) {
    nb::module_ m = root.def_submodule("common");

    m.attr("SDT_VERSION") = STRINGIFY(SDT_ver);
    m.attr("MACH1") = SDT_MACH1;
    m.attr("EARTH") = SDT_EARTH;
    m.attr("MICRO") = SDT_MICRO;
    m.attr("QUIET") = SDT_QUIET;

    m.def("blackman",
        [] (arr1d& sig) {
            SDT_blackman(sig.data(), sig.size());
        });
    m.def("exp_rand", &SDT_expRand);
    m.def("gaussian_1d", &SDT_gaussian1D);
    m.def("gravity", &SDT_gravity);

    m.def("haar",
        [] (arr1d& sig) {
            SDT_haar(sig.data(), sig.size());
        });

    m.def("hanning",
        [] (arr1d& sig) {
            SDT_hanning(sig.data(), sig.size());
        });

    m.def("ihaar",
        [] (arr1d& sig) {
            SDT_ihaar(sig.data(), sig.size());
        });

    m.def("kinetic", &SDT_kinetic);
    m.def("samples_in_air", &SDT_samplesInAir);
    m.def("samples_in_air_inv", &SDT_samplesInAir_inv);
    m.def("set_samplerate", &SDT_setSampleRate);

    m.def("sinc",
        [] (arr1d& sig, double f) {
            SDT_sinc(sig.data(), f, sig.size());
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
    add_common_submodule(m);
    add_liquids_submodule(m);
    add_resonators_submodule(m);
}