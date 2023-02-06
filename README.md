# miniRT

# Fuzzing

## Build and run docker
`docker build -t afl-glfw . && docker run -it -v /Users/sbos/Documents/Programming/Projects/miniRT/:/src afl-glfw`

## Compile for afl-cmin + afl-tmin, generate tests, and compile for AFL
`setup.sh`

## Fuzzing without generating coverage

### Start fuzzing
`fuzz.sh`

### Minimize any crash files
`minimize_crashes.sh`

## Fuzzing while generating coverage, for the Coverage Gutters VS Code extension
`coverage.sh`

## View the output of a scene from stdin
`< /src/scenes/valid/example.rt cat | afl-showmap -o /dev/null -- /src/miniRT_ctmin`

## Analyze crash 0 by coloring its characters based on criticality
`afl-analyze -i /src/afl/minimized-crashes/0 -- /src/miniRT_ctmin`
