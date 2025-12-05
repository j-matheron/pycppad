/*
 * Copyright 2025 INRIA
 */
#ifndef __pycppad_codegen_lang_c_lang_c_default_var_name_gen_hpp__
#define __pycppad_codegen_lang_c_lang_c_default_var_name_gen_hpp__

#include <cppad/cg/lang/c/lang_c_default_var_name_gen.hpp>
#include <nanobind/nanobind.h>

namespace pycppad {
namespace codegen {
namespace nb = nanobind;

template <typename Scalar> class LangCDefaultVariableNameGenerator {
public:
  typedef ::CppAD::cg::LangCDefaultVariableNameGenerator<Scalar>
      LangCDefaultVariableNameGeneratorType;

  static void
  expose(nb::module_ &m,
         const std::string &class_name = "LangCDefaultVariableNameGenerator") {
    nb::class_<LangCDefaultVariableNameGeneratorType>(m, class_name.c_str())
        .def(nb::init<std::string, std::string, std::string, std::string,
                      std::string>(),
             nb::arg("y"), nb::arg("x"), nb::arg("v"), nb::arg("array"),
             nb::arg("sarray"));
  }
};

} // namespace codegen
} // namespace pycppad
#endif // #ifndef __pycppad_codegen_lang_c_lang_c_default_var_name_gen_hpp__
