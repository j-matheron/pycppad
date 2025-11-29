#
# Copyright (c) 2021-2023 INRIA
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

SET(PROJECT_NAME pycppad)
SET(PROJECT_DESCRIPTION "Python bindings for CppAD and CppADCodeGen using Boost.Python")
SET(PROJECT_URL "https://github.com/simple-robotics/pycppad")
SET(PROJECT_CUSTOM_HEADER_EXTENSION "hpp")
SET(PROJECT_USE_CMAKE_EXPORT TRUE)
# To enable jrl-cmakemodules compatibility with workspace we must define the two
# following lines
SET(PROJECT_AUTO_RUN_FINALIZE FALSE)
SET(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})


# Project configuration
SET(PROJECT_USE_CMAKE_EXPORT TRUE)
SET(CMAKE_VERBOSE_MAKEFILE TRUE)
SET(CXX_DISABLE_WERROR TRUE)

# Check if the submodule cmake have been initialized
set(JRL_CMAKE_MODULES "${CMAKE_CURRENT_LIST_DIR}/cmake")
if(EXISTS "${JRL_CMAKE_MODULES}/base.cmake")
    message(STATUS "JRL cmakemodules found in 'cmake/' git submodule")
else()
    find_package(jrl-cmakemodules QUIET CONFIG)
    if(jrl-cmakemodules_FOUND)
        get_property(
            JRL_CMAKE_MODULES
            TARGET jrl-cmakemodules::jrl-cmakemodules
      PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "JRL cmakemodules found on system at ${JRL_CMAKE_MODULES}")
    else()
        message(STATUS "JRL cmakemodules not found. Let's fetch it.")
        include(FetchContent)
    FetchContent_Declare("jrl-cmakemodules"
                         GIT_REPOSITORY "https://github.com/jrl-umi3218/jrl-cmakemodules.git")
        FetchContent_MakeAvailable("jrl-cmakemodules")
    FetchContent_GetProperties("jrl-cmakemodules" SOURCE_DIR JRL_CMAKE_MODULES)
    endif()
endif()

# Use BoostConfig module distributed by boost library instead of using FindBoost module distributed
# by CMake
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()
INCLUDE(${JRL_CMAKE_MODULES}/base.cmake)
INCLUDE(${JRL_CMAKE_MODULES}/boost.cmake)
INCLUDE(${JRL_CMAKE_MODULES}/ide.cmake)
INCLUDE(${JRL_CMAKE_MODULES}/python.cmake)

# Project definition
COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
PROJECT(${PROJECT_NAME} ${PROJECT_ARGS})
CHECK_MINIMAL_CXX_STANDARD(11 ENFORCE)

# Project options
OPTION(SUFFIX_SO_VERSION "Suffix library name with its version" ON)
OPTION(PYCCPAD_WITH_CPPAD_CODEGEN "Build the python bindings for code generation (via CppADCodeGen)" OFF)
OPTION(PYCPPAD_WITH_BOOST_PYTHON "Builds a binding with boost python" OFF)
OPTION(PYCPPAD_WITH_NANOBIND "Builds a binding with nanobind" OFF)

SET_BOOST_DEFAULT_OPTIONS()
ADD_PROJECT_DEPENDENCY(Boost REQUIRED)
EXPORT_BOOST_DEFAULT_OPTIONS()

IF(PYCCPAD_WITH_CPPAD_CODEGEN)
  message(STATUS "Python bindings for code generation enabled")

  ADD_PROJECT_DEPENDENCY(cppadcg 2.4.1 REQUIRED PKG_CONFIG_REQUIRES "cppadcg >= 2.4.1" FIND_EXTERNAL "CppAD") # CppADCodeGen 2.4.1 is the first version to check the minimal version of CppAD
ENDIF()

ADD_PROJECT_DEPENDENCY(cppad 20180000.0 REQUIRED PKG_CONFIG_REQUIRES "cppad >= 20180000.0" FIND_EXTERNAL "CppAD")
ADD_PROJECT_DEPENDENCY(Eigen3 REQUIRED PKG_CONFIG_REQUIRES "eigen3 >= 3.0.5")

IF(PYCPPAD_WITH_BOOST_PYTHON)
  message(STATUS "boost.python binding enabled")

  SET(PYTHON_COMPONENTS Interpreter Development NumPy)
  FINDPYTHON(REQUIRED)
  ADD_PROJECT_DEPENDENCY(eigenpy 2.7.14 REQUIRED) 

  SET(${PROJECT_NAME}_HEADERS
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/fwd.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/ad.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/independent.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/ad_fun.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/cast.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/cppad.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/cppad-scalar.hpp
     ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/utils/scope.hpp)

  IF(PYCCPAD_WITH_CPPAD_CODEGEN)
      LIST(APPEND ${PROJECT_NAME}_HEADERS
      ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/codegen/cg.hpp
      ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/codegen/cppadcg-scalar.hpp
      ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/codegen/code-handler.hpp
      ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/codegen/lang/c/language-c.hpp
      ${PROJECT_SOURCE_DIR}/python/include/${PROJECT_NAME}/codegen/lang/c/lang-c-default-var-name-gen.hpp
  )
  ENDIF()

  ADD_SUBDIRECTORY(python)
ENDIF()

# Generated headers
LIST(APPEND (${PROJECT_NAME}_HEADERS
    ${${PROJECT_NAME}_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp
    ${${PROJECT_NAME}_BINARY_DIR}/include/${PROJECT_NAME}/deprecated.hpp
    ${${PROJECT_NAME}_BINARY_DIR}/include/${PROJECT_NAME}/warning.hpp)
)

if(PYCPPAD_WITH_NANOBIND)
  # find python for binding
  find_package(Python 3.8 REQUIRED COMPONENTS Interpreter Development.Module)

  # jrl-cmakemodules use PYTHON_EXECUTABLE defined in FINDPYTHON macro.
  # Since we doesn't call it in this branch, we must redefine it.
  set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})

    SET(${PROJECT_NAME}_HEADERS
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/fwd.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/ad.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/independent.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/ad_fun.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/cast.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/cppad.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/cppad-scalar.hpp
     ${PROJECT_SOURCE_DIR}/python-nb/include/${PROJECT_NAME}/utils/scope.hpp)

  # add associated subidirectory
  add_subdirectory(python-nb)
endif()

ADD_SUBDIRECTORY(example)

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})
PKG_CONFIG_APPEND_CFLAGS("-I${PYTHON_INCLUDE_DIRS}")
PKG_CONFIG_APPEND_BOOST_LIBS(${BOOST_COMPONENTS})

setup_project_finalize()
