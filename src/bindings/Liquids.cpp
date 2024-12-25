#include <nanobind/nanobind.h>
#include "../wrappers/Liquids.h"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(liquids, m) {
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
