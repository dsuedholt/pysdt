cmake_minimum_required(VERSION 3.30)

include(ExternalProject)

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
find_package(Python 3.10
  REQUIRED COMPONENTS Interpreter Development.Module
  OPTIONAL_COMPONENTS Development.SABIModule)

execute_process(
  COMMAND ${Python_EXECUTABLE} -m nanobind --cmake_dir
  OUTPUT_VARIABLE nanobind_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Import nanobind through CMake's find_package mechanism
find_package(nanobind CONFIG REQUIRED)

set(BINDINGS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/bindings)

find_library(SDT_PATH SDT HINTS sdt-libs/SDT_macosx_lib_83.0.0/SDT)
add_library(sdt SHARED IMPORTED src/wrappers/Macros.h)
set_target_properties(sdt
  PROPERTIES IMPORTED_LOCATION ${SDT_PATH}
)
set_target_properties(sdt
  PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${SDT_PATH}/Headers"
)

set(MODULE_LIST
  Liquids
  Resonators
)

foreach(moduleFile IN LISTS MODULE_LIST)
  string(TOLOWER ${moduleFile} moduleName)

  nanobind_add_module(
    ${moduleName} STABLE_ABI NB_SHARED ${BINDINGS_DIR}/${moduleFile}.cpp
  )

  set_target_properties(${moduleName}
    PROPERTIES INSTALL_RPATH "@loader_path;@loader_path/SDT.framework"
  )

  target_link_libraries(${moduleName} PRIVATE sdt)
  install(TARGETS ${moduleName} LIBRARY DESTINATION pysdt)
endforeach()


set_target_properties(nanobind
  PROPERTIES LIBRARY_OUTPUT_DIRECTORY pysdt
)
install(TARGETS nanobind LIBRARY DESTINATION pysdt)

install(IMPORTED_RUNTIME_ARTIFACTS sdt DESTINATION pysdt)