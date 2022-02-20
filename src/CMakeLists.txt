cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Boost COMPONENTS system REQUIRED)

# Try to use Qt6 if it's available, otherwise
# fall back to Qt5
find_package(Qt6 COMPONENTS Widgets)
if (NOT Qt6_FOUND)
    find_package(Qt5 5 COMPONENTS Widgets REQUIRED)
endif()

set(SOURCEFILES
    main.cpp

    data/factories/RequestRepositoryFactory.cpp
    data/repositories/FormdataRequestRepository.cpp
    data/repositories/RawRequestRepository.cpp

    domain/factories/RequestFactory.cpp
    domain/implementations/FormdataRequestBody.cpp
    domain/implementations/RawRequestBody.cpp
    domain/models/Request.cpp

    presentation/fragments/BodyFragment/BodyFragmentController.cpp
    presentation/fragments/BodyFragment/BodyFragmentView.cpp
    presentation/fragments/HeadersFragment/HeadersFragmentView.cpp
    presentation/fragments/HeadersFragment/HeadersFragmentController.cpp
    presentation/fragments/ResponseFragment/ResponseFragmentController.cpp
    presentation/fragments/ResponseFragment/ResponseFragmentView.cpp

    presentation/windows/MainWindow.cpp

    service/factories/RequestServiceFactory.cpp
    service/implementations/CppRestRequestService.cpp
)

add_executable(getit
    ${SOURCEFILES}
    ../resources/resources.qrc
)

# Link libraries
target_link_libraries(getit Boost::system)
target_link_libraries(getit cpprest)
target_link_libraries(getit nlohmann_json)

if (NOT Qt6_FOUND)
    target_link_libraries(getit Qt5::Widgets)
else()
    target_link_libraries(getit Qt::Widgets)
endif()