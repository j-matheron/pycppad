/*
 * Copyright 2025 INRIA
 */

#ifndef __pycppad_cppad_scalar_hpp__
#define __pycppad_cppad_scalar_hpp__

#include "pycppad/ad.hpp"
#include "pycppad/ad_fun.hpp"
#include "pycppad/independent.hpp"
#include <nanobind/stl/bind_vector.h>

// TODO uncomment when possible with nanobind
// #include <eigenpy/eigenpy.hpp>

namespace pycppad {
namespace nb = nanobind;
template <typename Scalar> void exposeCppADScalar(nb::module_ &m) {

  // TODO uncomment when possible with nanobind
  // typedef ::CppAD::AD<Scalar> ADScalar;
  // typedef Eigen::Matrix<ADScalar, Eigen::Dynamic, 1> VectorAD;
  // typedef Eigen::Matrix<ADScalar, 1, Eigen::Dynamic> RowVectorAD;

  using ADScalar = ::CppAD::AD<Scalar>;
  using ADVector = std::vector<ADScalar>;

  // TODO uncomment when possible with nanobind
  // eigenpy::exposeType<ADScalar>();
  // eigenpy::exposeType<ADScalar,Eigen::RowMajor>();

  nb::bind_vector<ADVector>(m, "ADVector");

  AD<Scalar>::expose(m);
  ADFun<Scalar>::expose(m);
  Independent<ADVector>::expose(m);
}
} // namespace pycppad

#endif // ifndef __pycppad_cppad_scalar_hpp__
