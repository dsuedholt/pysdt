cmake_minimum_required(VERSION 3.30)

include(FetchContent)

project(pysdt LANGUAGES CXX C)

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

set(SDT_SRC_DIR "SDT/src/SDT")

file(GLOB SDT_SOURCES
  "${SDT_SRC_DIR}/*.c"
  "SDT/3rdparty/json-parser/json.c"
  "SDT/3rdparty/json-builder/json-builder.c"
)

set_source_files_properties(${SDT_SOURCES} PROPERTIES LANGUAGE C)
add_library(sdt STATIC ${SDT_SOURCES})

if(UNIX)
  target_compile_options(sdt PRIVATE -fPIC)
endif()

target_include_directories(sdt PUBLIC
  "${SDT_SRC_DIR}"
  "SDT/3rdparty/json-parser"
  "SDT/3rdparty/json-builder"
)

# Try to import all Python components potentially needed by nanobind
find_package(Python
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule
)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

nanobind_add_module(_pysdt_impl STABLE_ABI NB_STATIC src/pysdt.cpp)

target_link_libraries(_pysdt_impl PRIVATE sdt)
install(TARGETS _pysdt_impl LIBRARY DESTINATION pysdt)