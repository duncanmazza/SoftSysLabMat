# LabMat

A MATLAB-inspired interpreted language supporting variable assignment; MATLAB-style matrix literals; and arithmetic and matrix operations.

Created as a [Software Systems](http://olin.smartcatalogiq.com/2020-21/Catalog/Courses-Credits-Hours/ENGR-Engineering/3000/ENGR3525) project by Duncan mazza and Junwon Lee at [Olin College of Engineering](https://www.olin.edu/). Read our final project report* here: [reports/report.md](./reports/report.md).

*\*Report valid for repository as of commit hash `2c3e958602c2083a594e0743075d38c14c235d14`*.

# Usage

Make sure to clone with the `--recurse-submodules` flag. To add a submodule that is present remotely after the fact, run: `git submodule update --init --remote`.

## Dependencies

Included as submodules:

- [mpc](https://github.com/orangeduck/mpc) - "...a lightweight and powerful Parser Combinator library for C."
- [GoogleTest](https://github.com/google/googletest) - a C++ test framework.

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

For information on how to use the language, refer to the project report: [reports/report.md](./reports/report.md).

## Unit tests

To run the unit tests, first follow the above compilation instructions. Then, from the `<project root>/build` directory:

```
cd tests/
./Google_Tests_run
```
