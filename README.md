[![C/C++ CI with Release](https://github.com/m4tveevm/file_analyzer/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/m4tveevm/file_analyzer/actions/workflows/c-cpp.yml)
# File Byte Frequency Analyzer

This program analyzes binary files to determine the frequency of each byte occurrence and displays the statistics in both table format and as a histogram.

## Usage

The program is executed via the command line with three arguments:

1. The name of the file to be analyzed.
2. The `-tr` flag to set the threshold value.
3. The threshold value itself - a decimal number between 0 and 1, which determines the threshold for highlighting bytes on the histogram in red.

### Command Format

```bash
./file_analyzer <filename> -tr <threshold value>
```

### Example

```bash
./file_analyzer example.bin -tr 0.1
```

This command will analyze the file `example.bin`, print the full byte usage statistics, and display a histogram. Bytes with a frequency of occurrence above 10% will be highlighted in red.

## Building from Source

To build the program from source, you'll need a C++ compiler that supports the C++17 standard and CMake. Follow these steps:

1. Clone the repository and navigate to the project directory.
2. Use CMake to configure the project and build the executable.

```bash
cmake -S . -B build
cmake --build build
```

The executable file `file_analyzer` will be located in the `build` directory.
