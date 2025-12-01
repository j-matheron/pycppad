/*
 * Copyright 2025 INRIA
 */

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"

// Use explicit template instantiation to build these
// function in different translation unit and avoid consuming
// too much memory on Windows
typedef ::CppAD::AD<double> ADScalar;

using ADScalar_d = ::CppAD::AD<double>;
using ADVector_d = std::vector<ADScalar_d>;

NB_MAKE_OPAQUE(ADVector_d);

namespace pycppad {

void enablePyCppAD(nb::module_ &m) { exposeCppADScalar<double>(m); }
} // namespace pycppad
