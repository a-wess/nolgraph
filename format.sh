#!/bin/bash
files=$(find src | grep ".cpp\|.hpp")
for file in $files
do
    clang-format -i -style="{
        BasedOnStyle: LLVM,
    }" $file
done
