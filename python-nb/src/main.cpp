/*
 * Copyright 2021 INRIA
 */

// TODO uncomment when possible with nanobind
// #include <Eigen/Core>
// #include <eigenpy/eigenpy.hpp>

#include "pycppad/cppad.hpp"

#include <nanobind/nanobind.h>

#include <nanobind/stl/string.h>

NB_MODULE(pycppad_pywrap_nb, m) {
  m.attr("__version__") = std::string(PYCPPAD_VERSION);
  m.attr("__raw_version__") = std::string(PYCPPAD_VERSION);

  pycppad::enablePyCppAD(m);
}
