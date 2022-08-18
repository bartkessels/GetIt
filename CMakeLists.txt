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
    add_subdirectory(packaging)
ELSE()
    # Only build test project when packaging is disabled
    add_subdirectory(tests)
ENDIF()

IF(APPLE)
    SET(qt_version "Qt6")
    execute_process(COMMAND brew --prefix OUTPUT_STRIP_TRAILING_WHITESPACE
            OUTPUT_VARIABLE BREW_PREFIX ERROR_QUIET)

    IF(NOT Qt6_DIR AND use_installed_dependencies)
        set(Qt6_DIR ${BREW_PREFIX}/opt/${qt_version}/lib/cmake/${qt_version})
    ENDIF()

    IF(NOT OPENSSL_ROOT_DIR AND use_installed_dependencies)
        set(OPENSSL_ROOT_DIR ${BREW_PREFIX}/opt/openssl@1.1)
    ENDIF()
ELSEIF(WIN32)
    IF(NOT Qt5_DIR)
        set(Qt5_DIR "C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5")
    ENDIF()

    IF(NOT OPENSSL_ROOT_DIR)
        set(OPENSSL_ROOT_DIR $ENV{PROGRAMFILES}/OpenSSL-Win64)
    ENDIF()
ENDIF()