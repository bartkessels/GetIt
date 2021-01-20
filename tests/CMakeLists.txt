cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

find_package(Boost COMPONENTS thread system chrono REQUIRED)

set(SRCFILES
    ../src/domain/body/FormdataRequestBody.cpp
    ../src/domain/body/RawRequestBody.cpp

    ../src/domain/pipelines/BodyPipeline.cpp
    ../src/domain/pipelines/HeadersPipeline.cpp
    ../src/domain/pipelines/MethodPipeline.cpp
    ../src/domain/pipelines/UriPipeline.cpp

    ../src/domain/request/CppRestRequest.cpp
    
    ../src/domain/Request.cpp
    ../src/domain/RequestData.cpp
    ../src/domain/RequestFactory.cpp
)

set(TST_SRCFILES
    main.cpp

    domain/body/tst_FormdataRequestBody.cpp
    domain/body/tst_RawRequestBody.cpp
    
    domain/pipelines/tst_BodyPipeline.cpp
    domain/pipelines/tst_HeadersPipeline.cpp
    domain/pipelines/tst_MethodPipeline.cpp
    domain/pipelines/tst_UriPipeline.cpp

    domain/request/tst_CppRestRequest.cpp

    domain/tst_RequestData.cpp
    domain/tst_RequestFactory.cpp
)

set(TST_HEADERFILES
    mocks/BeforePipelineMock.hpp
)

add_executable(getit_tests ${SRCFILES} ${TST_HEADERFILES} ${TST_SRCFILES})

# Include directories for dependencies
include_directories(../src)

# Libraries
target_link_libraries(getit_tests Boost::system)
target_link_libraries(getit_tests cpprest)
target_link_libraries(getit_tests trompeloeil Catch2::Catch2)

enable_testing()
add_test(NAME getit_tests COMMAND getit_tests)