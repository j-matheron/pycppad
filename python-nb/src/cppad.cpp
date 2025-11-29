/*
 * Copyright 2025 INRIA
 */

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"

// Use explicit template instantiation to build these
// function in different translation unit and avoid consuming
// too much memory on Windows
typedef ::CppAD::AD<double> ADScalar;

// TODO uncomment when possible with nanobind
// extern template void eigenpy::exposeType<ADScalar>();
// extern template void eigenpy::exposeType<ADScalar, Eigen::RowMajor>();

namespace pycppad {

void enablePyCppAD(nb::module_ &m) { exposeCppADScalar<double>(m); }
} // namespace pycppad
