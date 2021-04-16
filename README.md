# SoftSysLabMat

Taking inspiration from Matlab's admirable qualities and peculiar idiosyncrasies.

# Usage

Make sure to clone with the `--recurse-submodules` flag. To add a submodule that is present remotely after the fact, run: `git submodule update --init --remote`.

## Compilation

From the project root:

```
mkdir build && cd build
cmake ../
make -j12
```

## Execution

From the build directory created in the compilation step:

```
./LabMat
```

# Unit tests

This project implements unit tests with the [GoogleTest](https://github.com/google/googletest) unit testing library.

## Run unit tests

To run the unit tests, first follow the above compilation instructions. Then, from the `<project root>/build` directory:

```
cd tests/
./Google_Tests_run
```

# LabMat language



