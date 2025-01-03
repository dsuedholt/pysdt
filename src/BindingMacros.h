#pragma once

#define SDT_BIND_PROPERTY_RW(PYTHON_NAME, STRUCT_NAME, PROP_NAME, PROP_TYPE) \
    def_prop_rw(#PYTHON_NAME, \
        [] (STRUCT_NAME &self) { return self.get##PROP_NAME(); }, \
        [] (STRUCT_NAME &self, double PROP_NAME) { self.set##PROP_NAME(PROP_NAME); } \
    )