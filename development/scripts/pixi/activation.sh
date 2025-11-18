#! /bin/bash
# Activation script

# setup ccache
export CMAKE_CXX_COMPILER_LAUNCHER = ccache

# Create compile_commands.json for language server
export CMAKE_EXPORT_COMPILE_COMMANDS=1

# Activate color output with Ninja
export CMAKE_COLOR_DIAGNOSTICS=1