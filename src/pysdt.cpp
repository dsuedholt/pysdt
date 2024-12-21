#include <nanobind/nanobind.h>
#include <SDT/SDTCommon.h>

namespace nb = nanobind;

using namespace nb::literals;

NB_MODULE(pysdt, m) {
    m.doc() = "This is a \"hello world\" example with nanobind";
    m.def("fclip", SDT_fclip, "x"_a, "min"_a, "max"_a);
}
