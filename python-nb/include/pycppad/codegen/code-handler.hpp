/*
 * Copyright 2025 INRIA
 */
#ifndef __pycppad_codegen_code_handler_hpp__
#define __pycppad_codegen_code_handler_hpp__

#include <nanobind/nanobind.h>

#include "pycppad/codegen/cg.hpp"
#include <cppad/cg/code_handler.hpp>
#include <cppad/cg/lang/c/lang_c_default_var_name_gen.hpp>
#include <cppad/cg/lang/c/language_c.hpp>

namespace pycppad {
namespace codegen {

namespace nb = nanobind;

template <typename Scalar> class CodeHandler {
public:
  using CG = ::CppAD::cg::CG<Scalar>;
  using ADCG = ::CppAD::AD<CG>;
  using AD = ::CppAD::AD<Scalar>;

  // using VectorADCG = Eigen::Matrix<ADCG, Eigen::Dynamic, 1>;
  // using VectorAD = Eigen::Matrix<AD, Eigen::Dynamic, 1>;
  // using RowVectorADCG = Eigen::Matrix<ADCG, 1, Eigen::Dynamic>;
  // using VectorCG = Eigen::Matrix<CG, Eigen::Dynamic, 1>;
  // using RowVectorCG = Eigen::Matrix<CG, 1, Eigen::Dynamic>;
  // using RefVectorCG = Eigen::Ref<VectorCG>;
  // using RefRowVectorCG = Eigen::Ref<RowVectorCG>;

  using CGVector = std::vector<CG>;
  using ADCGVector = std::vector<ADCG>;

  using CodeHandlerType = ::CppAD::cg::CodeHandler<Scalar>;

  using LanguageC = ::CppAD::cg::LanguageC<Scalar>;
  using LangCDefaultVariableNameGenerator =
      ::CppAD::cg::LangCDefaultVariableNameGenerator<Scalar>;

public:
  static void expose(nb::module_ &m,
                     const std::string &class_name = "CodeHandler") {
    nb::class_<CodeHandlerType>(m, class_name.c_str())
        .def(nb::init<size_t>(), nb::arg("varCount"))
        .def("setReuseVariableIDs", &CodeHandlerType::setReuseVariableIDs,
             nb::arg("reuse"))
        .def("isReuseVariableIDs", &CodeHandlerType::isReuseVariableIDs)
        .def(
            "makeVariable",
            [](CodeHandlerType &self, CG &variable) {
              self.makeVariable(variable);
            },
            nb::arg("variable"),
            "Marks the provided variable as being an independent variable.\n"
            "Parameters:\n"
            "\tvariable: the variables that will become independent variable")
        .def(
            "makeVariable",
            [](CodeHandlerType &self, ADCG &variable) {
              self.makeVariable(variable);
            },
            nb::arg("variable"),
            "Marks the provided variable as being an independent variable.\n"
            "Parameters:\n"
            "\tvariable: the variables that will become independent variable")

        .def(
            "makeVariables",
            [](CodeHandlerType &self, CGVector &variables) {
              self.makeVariables(variables);
            },
            nb::arg("variables"),
            "Marks the provided variables as being independent variables.\n"
            "Parameters:\n"
            "\tvariables: the vector of variables that will become ")
        .def(
            "makeVariables",
            [](CodeHandlerType &self, ADCGVector &variables) {
              self.makeVariables(variables);
            },
            nb::arg("variables"),
            "Marks the provided variables as being independent variables.\n"
            "Parameters:\n"
            "\tvariables: the vector of variables that will become ")

        .def("getIndependentVariableSize",
             &CodeHandlerType::getIndependentVariableSize)
        .def("getIndependentVariableIndex",
             &CodeHandlerType::getIndependentVariableIndex, nb::arg("var"))
        .def("getMaximumVariableID", &CodeHandlerType::getMaximumVariableID)
        .def("isVerbose", &CodeHandlerType::isVerbose)
        .def("setVerbose", &CodeHandlerType::setVerbose)
        //.def("getJobTimer", &CodeHandler::getJobTimer)
        //.def("setJobTimer", &CodeHandler::setJobTimer, nb::args("jobTimer"))
        .def("isZeroDependents", &CodeHandlerType::isZeroDependents)
        .def("setZeroDependents", &CodeHandlerType::setZeroDependents,
             nb::arg("zeroDependents"))
        .def("getOperationTreeVisitId",
             &CodeHandlerType::getOperationTreeVisitId)
        .def("startNewOperationTreeVisit",
             &CodeHandlerType::startNewOperationTreeVisit)
        .def("isVisited", &CodeHandlerType::isVisited, nb::arg("node"))
        .def("markVisited", &CodeHandlerType::markVisited, nb::arg("node"))
        .def("getAtomicFunctionName", &CodeHandlerType::getAtomicFunctionName,
             nb::arg("id"),
             "Provides the name used by an atomic function with a given ID.\n"
             "Parameters:\n"
             "\tid:  the atomic function ID.")
        //.def("getExternalFuncMaxForwardOrder",
        //&CodeHandler::getExternalFuncMaxForwardOrder)
        //.def("getExternalFuncMaxReverseOrder",
        //&CodeHandler::getExternalFuncMaxReverseOrder)
        .def(
            "generateCode",
            [](CodeHandlerType &self, LanguageC &lang, CGVector &dependent,
               LangCDefaultVariableNameGenerator &nameGen,
               const std::string &jobName) {
              std::ostringstream oss;
              self.generateCode(oss, lang, dependent, nameGen, jobName);
              return oss.str();
            },
            nb::arg("lang"), nb::arg("dependent"), nb::arg("nameGen"),
            nb::arg("jobName"));
  }
};

} // namespace codegen
} // namespace pycppad

#endif // #ifndef __pycppad_codegen_code_handler_hpp__
