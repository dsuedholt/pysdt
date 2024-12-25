#include <nanobind/nanobind.h>
#include "../wrappers/Resonators.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(resonators, m) {
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