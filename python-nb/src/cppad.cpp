/*
 * Copyright 2025 INRIA
 */

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
#include "pycppad/codegen/cppadcg-scalar.hpp"
#endif

#include "pycppad/cppad-scalar.hpp"
#include "pycppad/cppad.hpp"

// Use explicit template instantiation to build these
// function in different translation unit and avoid consuming
// too much memory on Windows
typedef ::CppAD::AD<double> ADScalar;

using ADScalar_d = ::CppAD::AD<double>;
using ADVector_d = std::vector<ADScalar_d>;

NB_MAKE_OPAQUE(ADVector_d);

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS

using CGScalar_d = ::CppAD::cg::CG<double>;
using CGVector_d = std::vector<CGScalar_d>;

NB_MAKE_OPAQUE(CGVector_d);

using ADCGScalar_d = ::CppAD::AD<CGScalar_d>;
using ADCGVector_d = std::vector<ADCGScalar_d>;

NB_MAKE_OPAQUE(ADCGVector_d);
#endif

namespace pycppad {

void enablePyCppAD(nb::module_ &m) {
  exposeCppADScalar<double>(m);

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
  codegen::exposeCppADCGScalar<double>(m);
#endif
}
} // namespace pycppad
