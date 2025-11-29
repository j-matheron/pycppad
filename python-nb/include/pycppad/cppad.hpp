/*
 * Copyright 2025, INRIA
 */

#ifndef __pycppad_cppad_hpp__
#define __pycppad_cppad_hpp__

#include "pycppad/fwd.hpp"

namespace pycppad {
namespace nb = nanobind;

template <typename Scalar> void exposeCppADScalar(nb::module_ &m);

// que fait la ligne suivante ?
PYCPPAD_DLLAPI void enablePyCppAD(nb::module_ &m);
} // namespace pycppad

#endif // #ifndef __pycppad_cppad_hpp__
