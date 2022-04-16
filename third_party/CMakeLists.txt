cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(FetchContent)

# ------------------------------------------------------------------------------
# Trompeloeil
FetchContent_Declare(
    extern_trompeloeil

    GIT_REPOSITORY https://github.com/rollbear/trompeloeil.git
    GIT_TAG        v42)
FetchContent_MakeAvailable(extern_trompeloeil)

# ------------------------------------------------------------------------------
# Catch2
FetchContent_Declare(
    extern_catch2

    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.9)
FetchContent_MakeAvailable(extern_catch2)

# ------------------------------------------------------------------------------
# Cpp rest SDK
SET(BUILD_TESTS OFF)
SET(BUILD_SAMPLES OFF)

FetchContent_Declare(
        extern_restsdk

        GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
        GIT_TAG        2.10.18)
FetchContent_MakeAvailable(extern_restsdk)

SET(BUILD_TESTS ON)
SET(BUILD_SAMPLES ON)

# ------------------------------------------------------------------------------
# JSON
SET(JSON_BuildTests OFF)

FetchContent_Declare(
        extern_json

        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.10.5)
FetchContent_MakeAvailable(extern_json)