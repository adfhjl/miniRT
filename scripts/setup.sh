#!/bin/bash

cd /src

export AFL_LLVM_LAF_ALL=1

# TODO: Try to get "clang -fsanitize=address bar.c" working first
# TODO: Might not work well with parallelization "you should only run one afl-fuzz instance per sanitizer type."
# https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/fuzzing_in_depth.md#c-selecting-sanitizers
# export AFL_USE_ASAN=1

# TODO: Not sure if the DEBUG=1 is necessary for afl
# CC=afl-clang-lto make DEBUG=1
make DEBUG=1 AFL=1

mkdir -p afl

cd afl

mkdir -p first-minimized-scenes
rm -rf first-minimized-scenes/*
afl-cmin -i ../scenes -o first-minimized-scenes -- ../miniRT

mkdir -p trimmed-scenes
rm -rf trimmed-scenes/*
for file in first-minimized-scenes/**; do
afl-tmin -i "$file" -o trimmed-scenes/$(basename $file) -- ../miniRT
done

mkdir -p second-minimized-scenes
rm -rf second-minimized-scenes/*
afl-cmin -i trimmed-scenes -o second-minimized-scenes -- ../miniRT

bash
