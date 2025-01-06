#pragma once

#include <memory>

#define SDT_WRAP_STRUCT(STRUCT_NAME) \
private: \
    typedef void (*Deleter)(SDT##STRUCT_NAME*); \
    std::unique_ptr<SDT##STRUCT_NAME, Deleter> ptr; \
public: \
    STRUCT_NAME(const STRUCT_NAME&) = delete; \
    STRUCT_NAME(STRUCT_NAME&&) = delete; \
    template <typename ...Args> \
    explicit STRUCT_NAME(Args&& ...args) \
        : ptr(std::unique_ptr<SDT##STRUCT_NAME, Deleter>(SDT##STRUCT_NAME##_new(std::forward<Args>(args)...), SDT##STRUCT_NAME##_free)) {} \
    SDT##STRUCT_NAME* getRawPointer() { \
        return ptr.get(); \
    } \

#define SDT_WRAP_PROPERTY(STRUCT_NAME, PROP_NAME, PROP_TYPE) \
    PROP_TYPE get##PROP_NAME() const { \
        return SDT##STRUCT_NAME##_get##PROP_NAME(ptr.get()); \
    } \
    void set##PROP_NAME(const PROP_TYPE PROP_NAME) { \
        SDT##STRUCT_NAME##_set##PROP_NAME(ptr.get(), PROP_NAME); \
    } \

