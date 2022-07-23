cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

find_package(Boost COMPONENTS thread system chrono REQUIRED)

# Copy test_file.txt to current working directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/test_file.txt
        DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(SOURCEFILES
    ../src/data/factories/RequestRepositoryFactory.cpp
    ../src/data/repositories/FormDataRequestRepository.cpp
    ../src/data/repositories/RawRequestRepository.cpp
    ../src/data/repositories/RequestRepository.cpp

    ../src/domain/factories/RequestFactory.cpp
    ../src/domain/implementations/FormDataRequestBody.cpp
    ../src/domain/implementations/RawRequestBody.cpp
    ../src/domain/models/Request.cpp

    ../src/presentation/fragments/BodyFragment/BodyFragmentController.cpp
    ../src/presentation/fragments/HeadersFragment/HeadersFragmentController.cpp
    ../src/presentation/fragments/ResponseFragment/ResponseFragmentController.cpp

    ../src/presentation/windows/MainWindowViewModel.cpp

    ../src/service/factories/RequestServiceFactory.cpp
    ../src/service/implementations/CppRestRequestService.cpp
)

set(TESTFILES
    main.cpp

    data/factories/tst_RequestRepositoryFactory.cpp
    data/repositories/tst_FormDataRequestRepository.cpp
    data/repositories/tst_RawRequestRepository.cpp
    data/repositories/tst_RequestRepository.cpp

    domain/factories/tst_RequestFactory.cpp
    domain/implementations/tst_FormDataRequestBody.cpp
    domain/implementations/tst_RawRequestBody.cpp

    presentation/fragments/tst_BodyFragmentController.cpp
    presentation/fragments/tst_HeadersFragmentController.cpp
    presentation/fragments/tst_ResponseFragmentController.cpp

    presentation/windows/tst_MainWindowViewModel.cpp

    presentation/highlighters/tst_JsonSyntaxHighlighterRule.cpp

    service/factories/tst_RequestServiceFactory.cpp
    service/implementations/tst_CppRestRequestService.cpp
)

add_executable(getit_tests ${SOURCEFILES} ${TESTFILES})

include_directories(../src)

target_link_libraries(getit_tests Boost::system)
target_link_libraries(getit_tests cpprest)
target_link_libraries(getit_tests nlohmann_json::nlohmann_json)
target_link_libraries(getit_tests trompeloeil Catch2::Catch2)

enable_testing()
add_test(NAME getit_tests COMMAND getit_tests)