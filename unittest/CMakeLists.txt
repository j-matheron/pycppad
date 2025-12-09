cmake_minimum_required(VERSION 3.22)

project(ExtraLib CXX)

find_package(pycppad REQUIRED)


# Detect the installed nanobind package and import it into CMake
FIND_PACKAGE(Python 3.8 REQUIRED COMPONENTS Interpreter Development.Module)
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE
  OUTPUT_VARIABLE nanobind_ROOT)
find_package(nanobind CONFIG REQUIRED)
MAKE_DIRECTORY("${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")

nanobind_add_module(float_binding cppad_float.cpp)

target_link_libraries(float_binding PRIVATE pycppad::pycppad)


# test cppad interface binding with float 
include(CTest)

add_test (NAME add_eq_float_nb
  COMMAND ${Python_EXECUTABLE} add_eq_float_nb.py 
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
set_tests_properties(add_eq_float_nb
    PROPERTIES ENVIRONMENT "PYTHONPATH=${CMAKE_CURRENT_SOURCE_DIR}/build:$ENV{PYTHONPATH}")

