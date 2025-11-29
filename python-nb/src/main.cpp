/*
 * Copyright 2021 INRIA
 */

// TODO uncomment when possible with nanobind
// #include <Eigen/Core>
// #include <eigenpy/eigenpy.hpp>

#include "pycppad/cppad.hpp"

#include <nanobind/nanobind.h>

#include <sstream>

// inline std::string printVersion(const std::string &delimiter = ".") {
//   std::ostringstream oss;
//   oss << PYCPPAD_MAJOR_VERSION << delimiter << PYCPPAD_MINOR_VERSION
//       << delimiter << PYCPPAD_PATCH_VERSION;
//   return oss.str();
// }

// namespace nb = nanobind;

NB_MODULE(pycppad_pywrap_nb, m) {
  // bp::docstring_options module_docstring_options(true, true, false);
  //
  // m.attr("__version__") = printVersion();
  // m.attr("__raw_version__") = std::string(PYCPPAD_VERSION);
  //
  // TODO uncomment when possible with nanobind
  // eigenpy::enableEigenPy();

  pycppad::enablePyCppAD(m);
}
