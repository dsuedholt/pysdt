#pragma once

#include <memory>
#include <array>
#include <utility>
#include <string>

#define SDT_WRAP_STRUCT(STRUCT_NAME) \
private: \
    typedef void (*Deleter)(SDT##STRUCT_NAME*); \
    std::unique_ptr<SDT##STRUCT_NAME, Deleter> ptr; \
public: \
    STRUCT_NAME(const STRUCT_NAME&) = delete; \
    STRUCT_NAME(STRUCT_NAME&&) = delete; \
    template <typename ...Args> \
    explicit STRUCT_NAME(Args&& ...args) \
        : ptr(std::unique_ptr<SDT##STRUCT_NAME, Deleter>(SDT##STRUCT_NAME##_new(std::forward<Args>(args)...), &SDT##STRUCT_NAME##_free)) {} \
    SDT##STRUCT_NAME* getRawPointer() { \
        return ptr.get(); \
    } \

#define SDT_WRAP_REGISTRATION(STRUCT_NAME) \
private: \
    std::string name; \
public: \
    int register##STRUCT_NAME(std::string name) { \
        this->name = name; \
        return SDT_register##STRUCT_NAME(ptr.get(), name.c_str()); \
    } \
    int unregister##STRUCT_NAME() { \
        return SDT_unregister##STRUCT_NAME(name.c_str()); \
    } \
    ~STRUCT_NAME() { \
        unregister##STRUCT_NAME(); \
    } \


#define SDT_WRAP_PROPERTY(STRUCT_NAME, PROP_NAME, PROP_TYPE) \
    PROP_TYPE get##PROP_NAME() const { \
        return SDT##STRUCT_NAME##_get##PROP_NAME(ptr.get()); \
    } \
    void set##PROP_NAME(const PROP_TYPE PROP_NAME) { \
        SDT##STRUCT_NAME##_set##PROP_NAME(ptr.get(), PROP_NAME); \
    } \

#define SDT_WRAP_DSP(STRUCT_NAME) \
    double dsp() { \
        return SDT##STRUCT_NAME##_dsp(ptr.get()); \
    } \

#define SDT_WRAP_ANALYSIS_DSP(STRUCT_NAME, NUM_OUTS) \
    std::pair<bool, std::array<double, NUM_OUTS>> dsp(const double in) { \
        std::array<double, NUM_OUTS> dspOuts = {}; \
        bool updated = SDT##STRUCT_NAME##_dsp(ptr.get(), dspOuts.data(), in); \
        return {updated, dspOuts}; \
    } \

#define SDT_WRAP_DSP_MANY_OUT_WITH_INPUT(STRUCT_NAME, NUM_OUTS) \
    std::array<double, NUM_OUTS> dsp(const double in) { \
        std::array<double, NUM_OUTS> dspOuts = {}; \
        SDT##STRUCT_NAME##_dsp(ptr.get(), dspOuts.data(), in); \
        return dspOuts; \
    } \

#define SDT_WRAP_DSP_MANY_OUT_WITHOUT_INPUT(STRUCT_NAME, NUM_OUTS) \
    std::array<double, NUM_OUTS> dsp() { \
        std::array<double, NUM_OUTS> dspOuts = {}; \
        SDT##STRUCT_NAME##_dsp(ptr.get(), dspOuts.data()); \
        return dspOuts; \
    } \
