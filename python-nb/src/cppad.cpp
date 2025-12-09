/*
 * Copyright 2025 INRIA
 */

#include "pycppad/cppad.hpp"
#include "pycppad/cppad-scalar.hpp"

// Use explicit template instantiation to build these
// function in different translation unit and avoid consuming
// too much memory on Windows
using ADScalar = ::CppAD::AD<double>;

namespace pycppad {

void enablePyCppAD(nb::module_ &m) {
  exposeCppADScalar<double>(m);

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
  codegen::exposeCppADCGScalar<double>(m);
#endif
}
} // namespace pycppad
