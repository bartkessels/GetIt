cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

find_package(Boost COMPONENTS thread system chrono REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Copy tst_file.txt to current working directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/tst_file.txt
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

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

    ../src/gui/widget/BodyWidget/RawBodyTab/RawBodyTabController.cpp
    ../src/gui/widget/CookiesWidget/CookiesController.cpp
    ../src/gui/widget/HeadersWidget/HeadersController.cpp
    ../src/gui/widget/MethodWidget/MethodController.cpp
    ../src/gui/widget/UriWidget/UriController.cpp
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

    gui/widget/BodyWidget/RawBodyTab/tst_RawBodyTabController.cpp
    gui/widget/CookiesWidget/tst_CookiesController.cpp
    gui/widget/HeadersWidget/tst_HeadersController.cpp
    gui/widget/MethodWidget/tst_MethodController.cpp
    gui/widget/UriWidget/tst_UriController.cpp
)

set(TST_HEADERFILES
    gui/widget/BodyWidget/RawBodyTab/RawBodyTabViewMock.hpp
    gui/widget/CookiesWidget/CookiesViewMock.hpp
    gui/widget/HeadersWidget/HeadersViewMock.hpp
    gui/widget/MethodWidget/MethodViewMock.hpp
    gui/widget/UriWidget/UriViewMock.hpp
    
    mocks/AfterPipelineMock.hpp
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