cmake_minimum_required(VERSION 3.30)

include(FetchContent)

project(pysdt LANGUAGES CXX)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()

# Try to import all Python components potentially needed by nanobind
find_package(Python
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule
)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(_pysdt_impl STABLE_ABI NB_STATIC src/pysdt.cpp)
set_target_properties(_pysdt_impl PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

set(SDT_URL_BASE "https://github.com/SkAT-VG/SDT/releases/download/v83.0.0-Max3.1.0-Pd0.97.0")
set(SDT_BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/sdt-lib")
set(SDT_HEADER_DIR "${SDT_BASE_DIR}/include/SDT")
set(WHEELS_LIB_DIR ".libs")

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")

  FetchContent_Declare(sdtlib
    URL "${SDT_URL_BASE}/SDT_macosx_lib_83.0.0.zip"
    URL_HASH MD5=b7ae1f6f1c446103fa754a9899d00182
    SOURCE_DIR ${SDT_BASE_DIR}
  )
  set(SDT_LIB_FILE "${SDT_BASE_DIR}/SDT/SDT.framework/SDT")
  set(SDT_HEADER_DIR "${SDT_BASE_DIR}/SDT/SDT.framework/Headers")
  set_target_properties(_pysdt_impl PROPERTIES INSTALL_RPATH "@loader_path/.libs")
  add_library(sdt SHARED IMPORTED)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  FetchContent_Declare(sdtlib
    URL "${SDT_URL_BASE}/SDT_linux_lib_83.0.0.zip"
    URL_HASH MD5=7b28d61179284be9ff7919b6db005fc7
    SOURCE_DIR ${SDT_BASE_DIR}
  )
  set(SDT_LIB_FILE "${SDT_BASE_DIR}/lib/libSDT.so")
  set_target_properties(_pysdt_impl PROPERTIES INSTALL_RPATH "$ORIGIN/.libs")
  add_library(sdt SHARED IMPORTED)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  FetchContent_Declare(sdtlib
    URL "${SDT_URL_BASE}/SDT_win64_lib_83.0.0.zip"
    URL_HASH MD5=98454896065634b71c38c37d9d5981bb
    SOURCE_DIR ${SDT_BASE_DIR}
  )
  set(SDT_LIB_FILE "${SDT_BASE_DIR}/lib/libSDT64.dll")
  set(WHEELS_LIB_DIR "")
  add_library(sdt UNKNOWN IMPORTED)

else()
  message(FATAL_ERROR "Unsupported platform")
endif()

FetchContent_MakeAvailable(sdtlib)

get_filename_component(SDT_LIB_NAME "${SDT_LIB_FILE}" NAME)

file(RENAME ${SDT_LIB_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${SDT_LIB_NAME})

set_target_properties(sdt PROPERTIES
  IMPORTED_LOCATION ${SDT_LIB_NAME}
  IMPORT_NO_SONAME TRUE
  INTERFACE_INCLUDE_DIRECTORIES ${SDT_HEADER_DIR}
)

target_link_libraries(_pysdt_impl PRIVATE sdt)
install(TARGETS _pysdt_impl LIBRARY DESTINATION pysdt)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${SDT_LIB_NAME}" DESTINATION pysdt/${WHEELS_LIB_DIR})