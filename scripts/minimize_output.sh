#!/bin/bash

mkdir -p /src/afl/minimized-crashes
rm -rf /src/afl/minimized-crashes/*
i=0
for file in /src/afl/afl-output/master/crashes/id*; do
afl-tmin -i "$file" -o /src/afl/minimized-crashes/$i -- /src/miniRT_ctmin
i=$(($i + 1))
done

md5sum /src/afl/minimized-crashes/* | sort | awk 'BEGIN{lasthash = ""} $1 == lasthash {print $2} {lasthash = $1}' | xargs rm -f
