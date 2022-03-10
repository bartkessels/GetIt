#!/bin/env zsh

# Compile GetIt
echo 'Compiling GetIt...'
cmake ../../.
make GetIt

# Link Qt libraries
echo 'Linking Qt libraries'

# Link CppRestSdk libraries
echo 'Linking CppRestSdk libraries'

# Link Boost libraries
echo 'Linking Boost libraries'
