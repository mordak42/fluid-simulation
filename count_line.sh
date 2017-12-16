#!/bin/bash
find ./$1 -type f -name "*.cpp" -exec cat {} \; | sed '/^\s*$/d' | sed -e '/^\//d' | sed -e '/^\*\*/d' | sed -e '/^\*/d' | wc -l
find ./$1 -type f -name "*.hpp" -exec cat {} \; | sed '/^\s*$/d' | sed -e '/^\//d' | sed -e '/^\*\*/d' | sed -e '/^\*/d' | wc -l
exit 0
