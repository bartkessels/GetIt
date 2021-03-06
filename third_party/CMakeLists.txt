cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(FetchContent)

# ------------------------------------------------------------------------------
# Trompeloeil
FetchContent_Declare(
    extern_trompeloeil

    GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
    GIT_TAG        v39)
FetchContent_MakeAvailable(extern_trompeloeil)

# ------------------------------------------------------------------------------
# Catch2
FetchContent_Declare(
    extern_catch2

    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.4)
FetchContent_MakeAvailable(extern_catch2)

# ------------------------------------------------------------------------------
# Cpp rest SDK
SET(BUILD_TESTS OFF)
SET(BUILD_SAMPLES OFF)

FetchContent_Declare(
        extern_restsdk

        GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
        GIT_TAG        2.10.17)
FetchContent_MakeAvailable(extern_restsdk)

SET(BUILD_TESTS ON)
SET(BUILD_SAMPLES ON)
