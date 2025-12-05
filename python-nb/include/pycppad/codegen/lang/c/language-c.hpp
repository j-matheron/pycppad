/*
 * Copyright 2025 INRIA
 */
#ifndef __pycppad_codegen_lang_c_language_c_hpp__
#define __pycppad_codegen_lang_c_language_c_hpp__

#include <cppad/cg/lang/c/language_c.hpp>
#include <nanobind/nanobind.h>

namespace pycppad {
namespace codegen {
namespace nb = nanobind;

template <typename Scalar> class LanguageC {
public:
  using LanguageCType = ::CppAD::cg::LanguageC<Scalar>;

public:
  static void expose(nb::module_ &m,
                     const std::string &class_name = "LanguageC") {
    nb::class_<LanguageCType>(m, class_name.c_str(),
                              "C language source code generator")
        .def(nb::init<std::string, size_t>(), nb::arg("varTypeName"),
             nb::arg("spaces"));
  }
};

} // namespace codegen
} // namespace pycppad
#endif // #ifndef __pycppad_codegen_lang_c_language_c_hpp__
