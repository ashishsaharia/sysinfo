# SysInfo

SysInfo is a lightweight, fastfetch-style system information tool written in C++ for Linux.

---

## Requirements

- Linux
- CMake
- C++ compiler (GCC or Clang)

---

## Build

```bash
cmake -S . -B build
cmake --build build

Run without installing:

./build/sysinfo

Install as a Local Command (Optional)

To install sysinfo as a system command (/usr/local/bin/sysinfo):

cmake -S . -B build -DSYSINFO_INSTALL=ON
cmake --build build
sudo cmake --install build

After installation:

sysinfo

Uninstall

sudo rm /usr/local/bin/sysinfo
