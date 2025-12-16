cmake_minimum_required(VERSION 3.16)

project(sysinfo LANGUAGES CXX)

add_executable(sysinfo)
target_sources(sysinfo PRIVATE src/main.cxx)

# Option to install as system command
option(SYSINFO_INSTALL "Install sysinfo to /usr/local/bin" OFF)

if(SYSINFO_INSTALL)
    install(TARGETS sysinfo
            RUNTIME DESTINATION bin)
endif()

