# Cream Drop

Welcome to the Cream Drop repository. This project uses a Makefile for streamlined compilation and execution of various tasks related to the project.

## Features

- Efficient compilation and execution of project modules.
- Automated testing and performance reporting.
- Visualization of results using Python scripts.


## Prerequisites

Ensure you have the following installed:
- GCC/G++ Compiler
- Python 3
- Valgrind (for memory checks and cachegrind)
- gprof (for profiling)

## Makefile Commands

- `make all`: Compiles and runs the main program using the default target specified in the Makefile.
- `make puntoX.x`: Targets for specific parts of the project (replace `X` with the respective number to compile and run different parts of the project).
- `make plot`: Executes all parts of the project and uses Python scripts to generate plots from the output data.
- `make cachegrind`: Runs Valgrind's cachegrind on the main program for cache performance analysis.
- `make memcheck`: Runs Valgrind for memory leak checks on the main program.
- `make gprof`: Compiles the project with profiling enabled and generates a profiling report.
- `make test`: Compiles and runs unit tests using the Catch2 library.
- `make clean`: Removes all compiled files to clean up the directory.

## Compilation Details

- `CC=g++`: Compiler used is g++.
- `CFLAGS`: Includes optimization and sanitization flags for robust compilation.
- `GPROFFLAGS`, `CATCHFLAGS`, `MEMCHECKFLAGS`, `CACHEGRINDFLAGS`: Flags for profiling, testing, memory checking, and cache analysis respectively.

## Usage

To use the repository, you can start by cloning it and running a desired Makefile command. For example:

```bash
git clone https://github.com/juan3ltran/Cream_drop.git
cd Cream_drop
make all
