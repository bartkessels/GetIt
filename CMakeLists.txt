cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(GetIt
    VERSION 5.0.0
    DESCRIPTION "Open source REST client application"
    HOMEPAGE_URL "https://getit.bartkessels.net"
)

# Arguments
OPTION(use_installed_dependencies "Use installed dependencies from the system" false)
OPTION(packaging "Build the packages for GetIt" false)
option(use_qt6 "Enable this if you want to use Qt6 instead of Qt5" false)

# General project setup
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_XX_STANDARD 17)
set(CMAKE_XX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/build)

add_subdirectory(src)

# Only download packages when flag
IF (NOT use_installed_dependencies)
    add_subdirectory(third_party)
ENDIF()

# Only build packages when the -Dpackaging=true flag is set
IF (packaging)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    add_subdirectory(packaging)
    include(CPack)
ELSE()
    # Only build test project when packaging is disabled
    add_subdirectory(tests)
ENDIF()
