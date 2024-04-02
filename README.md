# CyberCore Engine

## Overview

Welcome to the CyberCore Engine repository! Here, you'll find the source code for a simple yet powerful engine designed for various applications. The repository is organized into several directories, each serving a specific purpose to streamline development and maintainability.

## Features

- **Source Code**: The `CyberCore` directory houses the source code files for the engine.
- **Executable Files**: Compiled executable files are stored in the `CyberCoreEngine` directory.
- **Supporting Scripts**: The `scripts` directory contains libraries and programs essential for engine functionality.

## Getting Started

To run the engine, follow these simple steps:

1. **Prepare Build Environment**: If CMake isn't installed, follow the instructions below based on your operating system.

   - **MacOS**: Install Homebrew by running `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`, then execute `brew install cmake` to install CMake.

2. **Build the Engine**:
```bash
mkdir build
cd build
cmake ..
make
```