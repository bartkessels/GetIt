cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Boost COMPONENTS system REQUIRED)

# Try to use Qt6 if it's available, otherwise
# fall back to Qt5
option(UseQt6 "Enable this if you want to use Qt6, instead of Qt5" no)

if (UseQt6)
    find_package(Qt6 COMPONENTS Widgets)
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
target_link_libraries(${CMAKE_PROJECT_NAME} cpprest)
target_link_libraries(${CMAKE_PROJECT_NAME} nlohmann_json)

if (UseQt6)
    target_link_libraries(${CMAKE_PROJECT_NAME} Qt::Widgets)
else()
    target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets)
endif()