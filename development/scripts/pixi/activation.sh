#! /bin/bash
# Activation script

# setup ccache
export CMAKE_CXX_COMPILER_LAUNCHER = ccache

# Create compile_commands.json for language server
export CMAKE_EXPORT_COMPILE_COMMANDS=1

# Activate color output with Ninja
export CMAKE_COLOR_DIAGNOSTICS=1

# Use boost.python as default binding
export WITH_BOOST_PY_BINDING=${WITH_BOOST_PY_BINDING:=OFF}

# Use cppadcg for codegen binding
export BUILD_WITH_CPPAD_CODEGEN_BINDINGS=${BUILD_WITH_CPPAD_CODEGEN_BINDINGS:=OFF}