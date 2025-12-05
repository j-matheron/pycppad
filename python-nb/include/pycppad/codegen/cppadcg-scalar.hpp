/*
 * Copyright 202() INRIA
 */

#ifndef __pycppad_cppad_codegen_cppadcg_scalar_hpp__
#define __pycppad_cppad_codegen_cppadcg_scalar_hpp__

#include <cppad/cg/cppadcg.hpp>

#include "pycppad/codegen/cg.hpp"
#include "pycppad/codegen/code-handler.hpp"
#include "pycppad/codegen/lang/c/lang-c-default-var-name-gen.hpp"
#include "pycppad/codegen/lang/c/language-c.hpp"

#include "pycppad/ad.hpp"
#include "pycppad/ad_fun.hpp"
#include "pycppad/independent.hpp"
#include <nanobind/stl/bind_vector.h>

namespace pycppad {
namespace codegen {
namespace nb = nanobind;

template <typename Scalar> void exposeCppADCGScalar(nb::module_ &m) {
  // TODO uncomment when possible with nanobind
  // typedef Eigen::Matrix<ADCGScalar, Eigen::Dynamic, 1> VectorADCG;
  // typedef Eigen::Matrix<ADCGScalar, 1, Eigen::Dynamic> RowVectorADCG;

  using CGScalar = ::CppAD::cg::CG<Scalar>;
  using GCVector = std::vector<CGScalar>;

  using ADCGScalar = ::CppAD::AD<CGScalar>;
  using ADCGVector = std::vector<ADCGScalar>;

  // TODO uncomment when possible with nanobind
  // eigenpy::exposeType<CGScalar>();
  // eigenpy::exposeType<CGScalar, Eigen::RowMajor>();
  // eigenpy::exposeType<ADCGScalar>();
  // eigenpy::exposeType<ADCGScalar, Eigen::RowMajor>();

  CG<Scalar>::expose(m, "CG");

  nb::bind_vector<GCVector>(m, "CGVector");
  nb::bind_vector<ADCGVector>(m, "ADCGVector");

  AD<CGScalar>::expose(m, "ADCG");
  ADFun<CGScalar>::expose(m, "ADCGFun");
  Independent<ADCGVector>::expose(m, "Independent");

  CodeHandler<Scalar>::expose(m, "CodeHandler");
  LanguageC<Scalar>::expose(m, "LanguageC");
  LangCDefaultVariableNameGenerator<Scalar>::expose(
      m, "LangCDefaultVariableNameGenerator");
}
} // namespace codegen
} // namespace pycppad

#endif // ifndef __pycppad_cppad_codegen_cppadcg_scalar_hpp__
