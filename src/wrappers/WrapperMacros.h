#pragma once

#define SDT_WRAP_STRUCT_PTR(STRUCT_NAME) \
private: \
    SDT##STRUCT_NAME *ptr; \
public: \

#define SDT_WRAP_DESTRUCTOR(STRUCT_NAME) \
    ~STRUCT_NAME() { \
        SDT##STRUCT_NAME##_free(ptr); \
    }

#define SDT_WRAP_DSP(STRUCT_NAME) \
    double dsp() { \
        return SDT##STRUCT_NAME##_dsp(ptr); \
    }

#define SDT_WRAP_STRUCT(STRUCT_NAME) \
    SDT_WRAP_STRUCT_PTR(STRUCT_NAME) \
    STRUCT_NAME() { \
        ptr = SDT##STRUCT_NAME##_new(); \
    } \
    SDT_WRAP_DESTRUCTOR(STRUCT_NAME) \


#define SDT_WRAP_STRUCT_WITH_ONE_ARG(STRUCT_NAME, ARG1_TYPE) \
    SDT_WRAP_STRUCT_PTR(STRUCT_NAME) \
    STRUCT_NAME() = delete; \
    STRUCT_NAME(ARG1_TYPE arg1) { \
        ptr = SDT##STRUCT_NAME##_new(arg1); \
    } \
    SDT_WRAP_DESTRUCTOR(STRUCT_NAME) \


#define SDT_WRAP_STRUCT_WITH_TWO_ARGS(STRUCT_NAME, ARG1_TYPE, ARG2_TYPE) \
    SDT_WRAP_STRUCT_PTR(STRUCT_NAME) \
    STRUCT_NAME() = delete; \
    STRUCT_NAME(ARG1_TYPE arg1, ARG2_TYPE arg2) { \
        ptr = SDT##STRUCT_NAME##_new(arg1, arg2); \
    } \
    SDT_WRAP_DESTRUCTOR(STRUCT_NAME) \


#define SDT_WRAP_PROPERTY(STRUCT_NAME, PROP_NAME, PROP_TYPE) \
    PROP_TYPE get##PROP_NAME() const { \
        return SDT##STRUCT_NAME##_get##PROP_NAME(ptr); \
    } \
    void set##PROP_NAME(const PROP_TYPE PROP_NAME) { \
        SDT##STRUCT_NAME##_set##PROP_NAME(ptr, PROP_NAME); \
    }