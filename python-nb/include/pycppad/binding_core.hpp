/*
 * Copyright 2025, INRIA
 */

#ifndef __pycppad_binding_core_hpp__
#define __pycppad_binding_core_hpp__

#include <nanobind/operators.h>
#include <nanobind/stl/bind_vector.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <cppad/cppad.hpp>

#ifdef PYCPPAD_WITH_CPPAD_CODEGEN_BINDINGS
#include <cppad/cg/cppadcg.hpp>
#endif

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

#endif // #ifndef __pycppad_binding_core_hpp__
