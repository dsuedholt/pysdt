#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <SDT/SDTCommon.h>
#include <SDT/SDTCommonMacros.h>

namespace nb = nanobind;
using namespace nb::literals;

using arr1d = nb::ndarray<double, nb::ndim<1>>;

NB_MODULE(common, m) {
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