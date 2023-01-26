#!/bin/bash

# afl-fuzz -i /src/afl/minimized-input -o /src/afl/afl-output -D -M master -- /src/miniRT @@
afl-fuzz -i /src/afl/minimized-input -o /src/afl/afl-output -D -M master -- /src/miniRT
