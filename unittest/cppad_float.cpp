/*
 * Copyright 2025 INRIA
 */

#include <nanobind/nanobind.h>

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
#include "pycppad/codegen/cppadcg-scalar.hpp"
#endif

#include <pycppad/cppad-scalar.hpp>

// Use explicit template instantiation to build these
// function in different translation unit and avoid consuming
// too much memory on Windows
using ADScalar = ::CppAD::AD<float>;

using ADScalar_f = ::CppAD::AD<float>;
using ADVector_f = std::vector<ADScalar_f>;

NB_MAKE_OPAQUE(ADVector_f);

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS

using CGScalar_f = ::CppAD::cg::CG<float>;
using CGVector_f = std::vector<CGScalar_f>;

NB_MAKE_OPAQUE(CGVector_f);

using ADCGScalar_f = ::CppAD::AD<CGScalar_f>;
using ADCGVector_f = std::vector<ADCGScalar_f>;

NB_MAKE_OPAQUE(ADCGVector_f);
#endif

namespace pycppad {

void enablePyCppAD(nb::module_ &m) {
  exposeCppADScalar<float>(m);

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
  codegen::exposeCppADCGScalar<float>(m);
#endif
}
} // namespace pycppad

NB_MODULE(float_binding, m) { pycppad::enablePyCppAD(m); }
