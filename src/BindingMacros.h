#pragma once

#define SDT_BIND_PROPERTY_RW(PYTHON_NAME, STRUCT_NAME, PROP_NAME, PROP_TYPE) \
    def_prop_rw(#PYTHON_NAME, \
        [] (STRUCT_NAME &self) { return self.get##PROP_NAME(); }, \
        [] (STRUCT_NAME &self, PROP_TYPE PROP_NAME) { self.set##PROP_NAME(std::move(PROP_NAME)); } \
    )

#define SDT_BIND_REGISTRATION(STRUCT_NAME) \
    def("register", &STRUCT_NAME::register##STRUCT_NAME) \
    .def("unregister", &STRUCT_NAME::unregister##STRUCT_NAME) \
