#! /bin/bash
# Activation script

# Set default build value only if not previously set
export PYCCPAD_BUILD_TYPE=${PYCCPAD_BUILD_TYPE:=Release}

# Use boost.python for python binding
export PYCPPAD_WITH_BOOST_PYTHON=${PYCPPAD_WITH_BOOST_PYTHON:=OFF}

# Use naobind for python binding
export PYCPPAD_WITH_NANOBIND=${PYCPPAD_WITH_NANOBIND:=OFF}

# Use cppadcg for codegen binding
export PYCCPAD_WITH_CPPAD_CODEGEN=${PYCCPAD_WITH_CPPAD_CODEGEN:=OFF}