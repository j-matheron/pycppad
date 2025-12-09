/*
 * Copyright 2025, INRIA
 */

#ifndef __pycppad_cppad_hpp__
#define __pycppad_cppad_hpp__

#include <nanobind/nanobind.h>

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
#include "pycppad/codegen/cppadcg-scalar.hpp"
#endif

#include "pycppad/fwd.hpp"

namespace pycppad {
namespace nb = nanobind;

template <typename Scalar> void exposeCppADScalar(nb::module_ &m);

void enablePyCppAD(nb::module_ &m);
} // namespace pycppad

#endif // #ifndef __pycppad_cppad_hpp__
