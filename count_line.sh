#!/bin/bash
find ./$1 -type f -name "*" -exec cat {} \; | sed '/^\s*$/d' | sed -e '/^\//d' | sed -e '/^\*\*/d' | sed -e '/^\*/d' | wc -l
exit 0
