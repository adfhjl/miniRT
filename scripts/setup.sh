#!/bin/bash

export AFL_LLVM_LAF_ALL=1

# These are mutually exclusive
export AFL_HARDEN=1
# TODO: Right now this prints "ld.lld: error: cannot open /usr/lib/llvm-14/lib/clang/14.0.6/lib/linux/libclang_rt.asan_static-x86_64.a: No such file or directory"
# TODO: Might not work well with parallelization "you should only run one afl-fuzz instance per sanitizer type."
# https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/fuzzing_in_depth.md#c-selecting-sanitizers
# export AFL_USE_ASAN=1

# TODO: Not sure if the DEBUG=1 is necessary for afl
make -C /src DEBUG=1 CTMIN=1

mkdir -p /src/afl

mkdir -p /src/afl/minimized-scenes
rm -rf /src/afl/minimized-scenes/*
afl-cmin -i /src/scenes -o /src/afl/minimized-scenes -- /src/miniRT_ctmin

mkdir -p /src/afl/trimmed-scenes
rm -rf /src/afl/trimmed-scenes/*
for file in /src/afl/minimized-scenes/**; do
afl-tmin -i "$file" -o /src/afl/trimmed-scenes/$(basename $file) -- /src/miniRT_ctmin
done


# TODO: Not sure if the DEBUG=1 is necessary for afl
make -C /src DEBUG=1 AFL=1
