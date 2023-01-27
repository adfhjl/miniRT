#!/bin/bash

cd /src

CC=afl-clang-fast make DEBUG=1

mkdir -p afl

cd afl

mkdir -p minimized-scenes
rm -rf minimized-scenes/*
# afl-cmin -i ../scenes -o minimized-scenes -- ../miniRT @@
afl-cmin -i ../scenes -o minimized-scenes -- ../miniRT
# cp ../scenes/invalid/* minimized-scenes

mkdir -p minimized-input
rm -rf minimized-input/*
i=0
for file in minimized-scenes/**; do
# afl-tmin -i "$file" -o minimized-input/$i -- ../miniRT @@
afl-tmin -i "$file" -o minimized-input/$i -- ../miniRT
i=$(($i + 1))
done

bash
