cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
include(FetchContent)

# Build dependencies


# ------------------------------------------------------------------------------
# Cpp rest SDK

IF (NOT cpprest_FOUND)
    FetchContent_Declare(
        extern_restsdk

        GIT_REPOSITORY https://github.com/microsoft/cpprestsdk.git
        GIT_TAG        2.10.18)
    FetchContent_MakeAvailable(extern_restsdk)
ENDIF()

# ------------------------------------------------------------------------------
# JSON

IF (NOT nlohmann_json_FOUND)
    FetchContent_Declare(
        extern_json

        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG        v3.10.5)
    FetchContent_MakeAvailable(extern_json)
ENDIF()

IF (NOT packaging) # Test dependencies

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

ENDIF()