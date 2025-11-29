/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_independent_hpp__
#define __pycppad_independent_hpp__

#include "pycppad/fwd.hpp"

#include <cppad/core/independent/independent.hpp>

// TODO uncomment when possible with nanobind
// #include <eigenpy/eigenpy.hpp>

namespace pycppad {
namespace nb = nanobind;

template <typename ADVector> struct Independent {

  // TODO uncomment when possible with nanobind
  // typedef Eigen::Ref<ADVector> RefADVector;

public:
  static void expose(nb::module_ &m, const std::string &name = "Independent") {
    m.def(
        name.c_str(),
        [](ADVector &x, const size_t abort_op_index_, bool record_compare_) {
          ADVector x_(x), dynamic(0);
          ::CppAD::Independent(x_, abort_op_index_, record_compare_, dynamic);
          return x_;
        },
        nb::arg("x"), nb::arg("abort_op_index") = 0,
        nb::arg("record_compare") = true, "Define a variable as Independent.");
  }
};
} // namespace pycppad
#endif // #ifndef __pycppad_ad_hpp__
