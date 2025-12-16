# SysInfo

![Linux](https://img.shields.io/badge/Platform-Linux-orange.svg)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

**SysInfo** is a lightweight, fastfetch-style system information tool written in C++ for Linux. It provides a clean, high-performance way to view your hardware and software specifications directly from the command line.

---

## 🛠 Requirements

Before compiling, ensure your system has the following dependencies:

* **Operating System:** Linux
* **Build System:** CMake (3.10+)
* **Compiler:** C++ compiler (GCC or Clang)

---

## 🚀 Building & Usage

### Build the Project
To compile the binary locally, navigate to the project root and run:

cmake -S . -B build
cmake --build build

Run Without Installing

After building, you can test the application immediately:
Bash

./build/sysinfo

📦 Installation

To install sysinfo as a global system command (/usr/local/bin/sysinfo), follow these steps:


Build and Install:
    cmake -S . -B build -DSYSINFO_INSTALL=ON
    cmake --build build
    sudo cmake --install build

Now you can simply type sysinfo in any terminal window.

🗑️ Uninstallation

If you wish to remove the tool from your system, run the following command:

sudo rm /usr/local/bin/sysinfo


📄 License

Distributed under the MIT License. See LICENSE for more information.

