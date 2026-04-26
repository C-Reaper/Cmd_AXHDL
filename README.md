# Project README

## Overview
The project is a collection of tools and scripts for developing software across different platforms using C/C++. It includes support for building applications on Linux, Windows, cross-compiling for Windows on Linux, and compiling for WebAssembly.

## Features
- **Multi-platform support**: Build and run applications on Linux, Windows, and WebAssembly.
- **Code organization**: Clean separation of source code, libraries, and build configurations.
- **Build automation**: Utilizes Makefiles to streamline the build process.

## Project Structure
The project structure is organized as follows:

```
<Project>/
├── build/              # .exe files produced by Main.c
├── libs/               # *.c for bin
├── lib/                # librarys for my own languages
├── code/               # scripts from my custom languages for example .rex, .ll, .omml
├── data/               # Datafile for example .txt or dumped files
├── assets/             # images and sound files
├── src/                # src code
│   ├── Main.c          # Entry point
│   └── *.h             # stand alone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
├── Makefile.wine       # Wine Build configuration
└── README.md           # This file
```

### Prerequisites
- **C/C++ Compiler and Debugger**: GCC for Linux, Clang for cross-compilation on Linux.
- **Make utility**: Required for building the project.
- **Standard development tools**: Essential for compiling and linking C/C++ code.
- **Libraries**: Depending on the platform, additional libraries may be required. For example:
  - **Linux**: None specified in the structure.
  - **Windows**: WINAPI, X11, ALSA.
  - **WebAssembly**: Emscripten or wasmtime.

## Build & Run
### Linux
To build and run the project on Linux:

```sh
cd <Project>
make -f Makefile.linux all
make -f Makefile.linux exe
```

To clean and rebuild:

```sh
make -f Makefile.linux clean
make -f Makefile.linux all
```

### Windows
To build and run the project on Windows:

```sh
cd <Project>
make -f Makefile.windows all
make -f Makefile.windows exe
```

To clean and rebuild:

```sh
make -f Makefile.windows clean
make -f Makefile.windows all
```

### Cross-compiling for Windows on Linux
To cross-compile for Windows on Linux:

```sh
cd <Project>
make -f Makefile.wine all
make -f Makefile.wine exe
```

To clean and rebuild:

```sh
make -f Makefile.wine clean
make -f Makefile.wine all
```

### WebAssembly
To build for WebAssembly:

```sh
cd <Project>
make -f Makefile.web all
make -f Makefile.web exe
```

To clean and rebuild:

```sh
make -f Makefile.web clean
make -f Makefile.web all
```

---

This README provides a comprehensive overview of the project, its features, and how to build and run it across different platforms.