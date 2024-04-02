# cccompression

![](https://github.com/eoan-ermine/cccompression/actions/workflows/style.yaml/badge.svg) ![](https://github.com/eoan-ermine/cccompression/actions/workflows/cppcheck.yaml/badge.svg) ![](https://github.com/eoan-ermine/cccompression/actions/workflows/analyze.yaml/badge.svg) ![](https://github.com/eoan-ermine/cccompression/actions/workflows/linux-gcc.yaml/badge.svg) ![](https://github.com/eoan-ermine/cccompression/actions/workflows/linux-clang.yaml/badge.svg) ![](https://github.com/eoan-ermine/cccompression/actions/workflows/documentation.yaml/badge.svg)

Write Your Own Compression Tool in C++

## Dependencies

| Package              | Version |
| -------------------- | ------- |
| Boost.ProgramOptions | >=1.74  |

**Development dependencies**

| Package      | Version  |
| ------------ | -------- |
| clang-format | >= 17    |

**SAST Tools**

1. [PVS-Studio](https://pvs-studio.ru/ru/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source) - static analyzer for C, C++, C#, and Java code.
2. [Cppcheck](https://cppcheck.sourceforge.io/) — statis analysis tool for C/C++ code.

### Installation

#### Ubuntu

```shell
# Install Boost.Program Options
sudo apt install libboost-program-options-dev
# Install LLVM
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 18
```

**Development dependencies**:

```shell
sudo apt install clang-format
sudo apt install cppcheck
# For installation of PVS-Studio see PVS-Studio docs: https://pvs-studio.com/en/docs/manual/0039/#ID3ABD56C167
```

#### Arch

```shell
sudo pacman -S boost
```

**Development dependencies**:

```shell
sudo pacman -S clang # For clang-format
sudo pacman -S cppcheck
# For installation of PVS-Studio see PVS-Studio docs: https://pvs-studio.com/en/docs/manual/0039/#ID3ABD56C167

```

## Getting the Source Code and Building cccompression

1. Check out cccompression:
  * `git clone git@github.com:eoan-ermine/cccompression.git`
  * Or, on windows:
  `git clone --config core.autocrlf=false git@github.com:eoan-ermine/cccompression.git`
2. Configure and build cccompression:
  * `cd cccompression`
  * `cmake -S . -B build -G <generator>`
    Some common build system generators are:
      * Ninja — for generating Ninja build files
      * Unix Makefiles — for generating make-compatible parallel makefiles
      * Visual Studio — for generating Visual Studio projects and solutions
      * Xcode — for generating Xcode projects
  * `cmake --build build [--target <target>]`
    * The default target (i.e `cmake --build build` or `make -C build`) will build all cccompression
    * The `check-all` target (i.e `ninja check-all`) will run the regression tests to ensure everything is in working order
    * The `format` target (i.e `ninja format`) will run clang-format on all project files
    * The `check-format` target (i.e `ninja check-format`) will verify that project's code follows formatting conventions
    * The `docs` target (i.e `ninja docs`) will generate documentation using doxygen
    * The `cppcheck` target (i.e `ninja cppcheck`) will run cppcheck on all project files
    * The `pvs-studio` target (i.e `ninja pvs-studio`) will run PVS-Studio on all project files
