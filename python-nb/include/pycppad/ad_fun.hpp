/*
 * Copyright 2021-2022 INRIA
 */

#ifndef __pycppad_ad_fun_hpp__
#define __pycppad_ad_fun_hpp__

#include "nanobind/nanobind.h"
#include "pycppad/fwd.hpp"
#include <cstddef>
#include <nanobind/stl/vector.h>

namespace pycppad {
namespace nb = nanobind;

template <typename Scalar> class ADFun {
  // TODO uncomment when possible with nanobind
  // typedef ::CppAD::ADFun<Scalar> ADFun;
  // typedef Eigen::Matrix<::CppAD::AD<Scalar>, Eigen::Dynamic, 1> ADVector;
  // typedef Eigen::Ref<ADVector> RefADVector;
  // typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> Vector;

  typedef ::CppAD::AD<Scalar> ADScalar;
  typedef ::CppAD::ADFun<Scalar> ADFunType;
  typedef std::vector<ADScalar> ADVector;
  typedef std::vector<Scalar> Vector;

public:
  static Vector Forward_multiple(ADFunType &f, size_t q, const Vector &xq) {
    return f.Forward(q, xq);
  }

private:
  static void Dependent(ADFunType &self, ADVector &x, ADVector &y) {
    self.Dependent(x, y);
  }

public:
  static void expose(nb::module_ &m, const std::string &class_name = "ADFun") {
    nb::class_<ADFunType>(m, class_name.c_str())
        .def(nb::init<>())
        .def(
            "__init__",
            [](ADFunType *self, ADVector &x, ADVector &y) {
              ADVector x_(x), y_(y);
              new (self) ADFunType(x_, y_);
              x = x_;
              y = y_;
            },
            nb::arg("x"), nb::arg("y"))
        .def("from_json", &ADFunType::from_json, nb::arg("json"))

        .def("size_order", &ADFunType::size_order)
        .def("Dependent", &Dependent, nb::arg("x"), nb::arg("y"))

        // Forward
        .def(
            "Forward",
            [](ADFunType &self, size_t q, size_t r, const Vector &xq) {
              return self.Forward(q, r, xq);
            },
            nb::arg("q"), nb::arg("r"), nb::arg("x"))
        .def("Forward", &Forward_multiple, nb::arg("q"), nb::arg("xq"))

        // Reverse
        .def(
            "Reverse",
            [](ADFunType &self, size_t p, const Vector &v) {
              return self.Reverse(p, v);
            },
            nb::arg("p"), nb::arg("v"))

        // Hessian
        .def(
            "Hessian",
            [](ADFunType &self, const Vector &x, const Vector &w) {
              return self.Hessian(x, w);
            },
            nb::arg("x"), nb::arg("w"))
        .def(
            "Hessian",
            [](ADFunType &self, const Vector &x, size_t i) {
              return self.Hessian(x, i);
            },
            nb::arg("x"), nb::arg("i"))

        // Jacobian
        .def(
            "Jacobian",
            [](ADFunType &self, const Vector &x) { return self.Jacobian(x); },
            nb::arg("x"))

        // optimize
        .def("optimize", &ADFunType::optimize);
  }
};
} // namespace pycppad
#endif // #ifndef __pycppad_ad_hpp__
