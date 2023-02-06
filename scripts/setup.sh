#!/bin/bash

cd /src

export AFL_LLVM_LAF_ALL=1

# TODO: Try to get "clang -fsanitize=address bar.c" working first
# TODO: Might not work well with parallelization "you should only run one afl-fuzz instance per sanitizer type."
# https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/fuzzing_in_depth.md#c-selecting-sanitizers
# export AFL_USE_ASAN=1

# TODO: Not sure if the DEBUG=1 is necessary for afl
make DEBUG=1 CTMIN=1


mkdir -p afl

cd afl

mkdir -p minimized-scenes
rm -rf minimized-scenes/*
afl-cmin -i ../scenes -o minimized-scenes -- ../miniRT_ctmin

mkdir -p trimmed-scenes
rm -rf trimmed-scenes/*
for file in minimized-scenes/**; do
afl-tmin -i "$file" -o trimmed-scenes/$(basename $file) -- ../miniRT_ctmin
done


cd /src

# TODO: Not sure if the DEBUG=1 is necessary for afl
make DEBUG=1 AFL=1
