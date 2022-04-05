cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

IF (APPLE)
    add_subdirectory(macos)
ENDIF()

IF (WINDOWS)
    add_subdirectory(windows)
ENDIF()

IF (LINUX)
    add_subdirectory(linux)
ENDIF()