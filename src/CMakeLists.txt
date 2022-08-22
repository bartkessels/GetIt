cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Boost COMPONENTS system REQUIRED)
find_package(OpenSSL REQUIRED)

if (use_installed_dependencies)
    find_package(nlohmann_json REQUIRED)
    find_package(cpprestsdk REQUIRED)
endif()

if (use_qt6)
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()

set(SOURCEFILES
    main.cpp

    data/factories/RequestRepositoryFactory.cpp
    data/repositories/FormDataRequestRepository.cpp
    data/repositories/RawRequestRepository.cpp
    data/repositories/RequestRepository.cpp

    domain/factories/RequestFactory.cpp
    domain/implementations/FormDataRequestBody.cpp
    domain/implementations/RawRequestBody.cpp
    domain/models/Request.cpp

    presentation/fragments/BodyFragment/BodyFragmentController.cpp
    presentation/fragments/BodyFragment/BodyFragmentView.cpp
    presentation/fragments/HeadersFragment/HeadersFragmentView.cpp
    presentation/fragments/HeadersFragment/HeadersFragmentController.cpp
    presentation/fragments/ResponseFragment/ResponseFragmentController.cpp
    presentation/fragments/ResponseFragment/ResponseFragmentView.cpp

    presentation/highlighters/SyntaxHighlighter.cpp

    presentation/windows/MainWindow.cpp
    presentation/windows/MainWindowViewModel.cpp

    service/factories/RequestServiceFactory.cpp
    service/implementations/CppRestRequestService.cpp
)

add_executable(
        ${CMAKE_PROJECT_NAME}
        ${SOURCEFILES}
        ../resources/resources.qrc
)


install(TARGETS ${CMAKE_PROJECT_NAME}
        RUNTIME
        DESTINATION bin
)

# Link libraries
target_link_libraries(${CMAKE_PROJECT_NAME} Boost::system)
target_link_libraries(${CMAKE_PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${CMAKE_PROJECT_NAME} cpprest)
target_link_libraries(${CMAKE_PROJECT_NAME} nlohmann_json::nlohmann_json)

if (use_qt6)
    target_link_libraries(${CMAKE_PROJECT_NAME} Qt::Widgets)
else()
    target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets)
endif()