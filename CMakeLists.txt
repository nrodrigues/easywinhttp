cmake_minimum_required (VERSION 2.8)

project (easywinhttp)

add_definitions (
    -DUNICODE
    -D_UNICODE
)

include_directories (include)

add_subdirectory (src)

configure_file (easywinhttp-config.cmake.in easywinhttp-config.cmake @ONLY)

export (PACKAGE easywinhttp)
export (TARGETS easywinhttp FILE easywinhttp-targets.cmake)

install (FILES easywinhttp-config.cmake
    DESTINATION CMake
    COMPONENT dev
)
