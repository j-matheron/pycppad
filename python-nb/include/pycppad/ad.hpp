/*
 * Copyright 2021 INRIA
 */

#ifndef __pycppad_ad_hpp__
#define __pycppad_ad_hpp__

#include "nanobind/nanobind.h"
#include "pycppad/cast.hpp"
#include "pycppad/fwd.hpp"

// TODO uncomment when possible with nanobind
// #include <eigenpy/ufunc.hpp>
// #include <eigenpy/user-type.hpp>

namespace pycppad {
namespace nb = nanobind;

template <typename Scalar> class AD {
public:
  typedef ::CppAD::AD<Scalar> ADType;

public:
  static void expose(nb::module_ &m, const std::string &class_name = "AD") {
    nb::class_<ADType>(m, class_name.c_str())
        .def(nb::init<>())
        .def(nb::init<Scalar>(), nb::arg("value"))
        .def(nb::init<ADType>(), nb::arg("other"))

        .def(nb::self + nb::self)
        .def(nb::self - nb::self)
        .def(nb::self * nb::self)
        .def(nb::self / nb::self)
        .def(nb::self += nb::self)
        .def(nb::self /= nb::self)
        .def(nb::self -= nb::self)
        .def(nb::self *= nb::self)

        .def("abs_me", &ADType::abs_me)
        .def("acos_me", &ADType::acos_me)
        .def("asin_me", &ADType::asin_me)
        .def("atan_me", &ADType::atan_me)
        .def("cos_me", &ADType::cos_me)
        .def("cosh_me", &ADType::cosh_me)
        .def("exp_me", &ADType::exp_me)
        .def("fabs_me", &ADType::fabs_me)
        .def("log_me", &ADType::log_me)
        .def("sin_me", &ADType::sin_me)
        .def("sign_me", &ADType::sign_me)
        .def("sinh_me", &ADType::sinh_me)
        .def("sqrt_me", &ADType::sqrt_me)
        .def("tan_me", &ADType::tan_me)
        .def("tanh_me", &ADType::tanh_me)
        .def("asinh_me", &ADType::asinh_me)
        .def("acosh_me", &ADType::acosh_me)
        .def("atanh_me", &ADType::atanh_me)
        .def("erf_me", &ADType::erf_me, nb::arg("complement"))
        .def("expm1_me", &ADType::expm1_me)
        .def("log1p_me", &ADType::log1p_me)

        //.def("__str__",
        //     [](const ADType &self) {
        //       std::stringstream ss;
        //       ss << "AD(" << self << ")";
        //       return ss.str();
        //     })
        //.def("__repr__",
        //     [](const ADType &self) {
        //       std::stringstream ss;
        //       ss << "AD(" << self << ")";
        //       return ss.str();
        //     })

        .def("__float__",
             [](const ADType &self) { return ::CppAD::Value(self); })
        .def("__int__", [](const ADType &self) {
          return static_cast<int64_t>(::CppAD::Value(self));
        });

    m.def(
        "Value", [](const ADType &x) { return ::CppAD::Value(x); },
        nb::arg("x"), "Conversion from AD to Base type");

    // TODO uncomment when possible with nanobind

    // eigenpy::registerNewType<AD>();
    // eigenpy::registerCommonUfunc<AD>();
    //
    // eigenpy::registerCast<AD,double>(false);
    // eigenpy::registerCast<double,AD>(true);
    // eigenpy::registerCast<AD,float>(false);
    // eigenpy::registerCast<float,AD>(true);
    // eigenpy::registerCast<AD,long>(false);
    // eigenpy::registerCast<long,AD>(true);
    // eigenpy::registerCast<AD,int>(false);
    // eigenpy::registerCast<int,AD>(true);
  }
};
} // namespace pycppad

#endif // #ifndef __pycppad_ad_hpp__
