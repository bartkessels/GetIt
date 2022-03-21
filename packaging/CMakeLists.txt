cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})

set(CPACK_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Bart Kessels")
set(CPACK_PACKAGE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(CPACK_PACKAGE_ICON ../resources/icons/main.svg)
set(CPACK_SOURCE_IGNORE_FILES *test)
set(CPACK_COMPONENTS_ALL_IN_ONE_PACKAGE 1)

IF (APPLE)
    add_subdirectory(macos)
ENDIF()

IF (WINDOWS)
    add_subdirectory(windows)
ENDIF()

IF (LINUX)
    add_subdirectory(linux)
ENDIF()