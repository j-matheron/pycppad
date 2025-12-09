/*
 * Copyright 2025 INRIA
 */

#ifndef __pycppad_codegen_cg_hpp__
#define __pycppad_codegen_cg_hpp__

#include <cppad/cg/cppadcg.hpp>
#include <nanobind/nanobind.h>

#include "pycppad/binding_core.hpp"
#include "pycppad/cast.hpp"

namespace pycppad {

namespace internal {
template <typename Scalar> struct CppADValue<::CppAD::cg::CG<Scalar>> {
  static const Scalar &get(const ::CppAD::AD<::CppAD::cg::CG<Scalar>> &v) {
    return ::CppAD::Value<::CppAD::cg::CG<Scalar>>(v).getValue();
  }
};

template <typename Scalar, typename To>
struct Cast<::CppAD::cg::CG<Scalar>, To> {
  using From = ::CppAD::cg::CG<Scalar>;
  static To run(const From &from) {
    return static_cast<To>(::CppAD::Value<From>(from).getValue());
  }
};
} // namespace internal

namespace codegen {

namespace nb = nanobind;

template <typename Scalar> class CG {

public:
  using CGType = ::CppAD::cg::CG<Scalar>;

public:
  static void expose(nb::module_ &m, const std ::string &class_name = "CG") {
    nb::class_<CGType>(m, class_name.c_str())
        .def(nb::init<>())
        .def(nb::init<Scalar>(), nb::arg("value"))
        .def(nb::init<CGType>(), nb::arg("other"))

        .def("isIdenticalZero", &CGType::isIdenticalZero)
        .def("isIdenticalOne", &CGType::isIdenticalOne)
        .def("isValueDefined", &CGType::isValueDefined)
        .def("isParameter", &CGType::isParameter)
        .def("isVariable", &CGType::isVariable)

        .def(nb::self + nb::self)
        .def(nb::self - nb::self)
        .def(nb::self * nb::self)
        .def(nb::self / nb::self)
        .def(nb::self += nb::self)
        .def(nb::self -= nb::self)
        .def(nb::self *= nb::self)
        .def(nb::self /= nb::self)
        .def(-nb::self)

        .def("value", [](const CGType &self) { return self.getValue(); })

        .def("__str__",
             [](const CGType &self) {
               std::stringstream ss;
               ss << "CG(" << self << ")";
               return ss.str();
             })
        .def("__repr__",
             [](const CGType &self) -> std::string {
               std::stringstream ss;
               ss << "CG(" << self << ")";
               return ss.str();
             })
        .def("__float__", [](const CGType &self) { return self.getValue(); })
        .def("__int__", internal::Cast<CGType, int64_t>::run);

    // TODO uncomment when possible with nanobind

    // eigenpy::registerNewType<CG>();
    // eigenpy::registerCommonUfunc<CG>();
    //
    // eigenpy::registerCast<CG, double>(false);
    // eigenpy::registerCast<double, CG>(true);
    // eigenpy::registerCast<CG, float>(false);
    // eigenpy::registerCast<float, CG>(true);
    // eigenpy::registerCast<CG, long>(false);
    // eigenpy::registerCast<long, CG>(true);
    // eigenpy::registerCast<CG, int>(false);
    // eigenpy::registerCast<int, CG>(true);
  }
};
} // namespace codegen
} // namespace pycppad

#endif // #ifndef __pycppad_codegen_cg_hpp__
