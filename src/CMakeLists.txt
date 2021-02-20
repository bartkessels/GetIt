cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(SOURCEFILES
    main.cpp

    domain/body/FormdataRequestBody.cpp
    domain/body/RawRequestBody.cpp

    domain/pipelines/BodyPipeline.cpp
    domain/pipelines/HeadersPipeline.cpp
    domain/pipelines/MethodPipeline.cpp
    domain/pipelines/UriPipeline.cpp

    domain/request/CppRestRequest.cpp

    domain/Request.cpp
    domain/RequestData.cpp
    domain/RequestFactory.cpp

    gui/MainWindow/MainWindow.cpp

    gui/widget/CookiesWidget/CookiesController.cpp
    gui/widget/CookiesWidget/CookiesView.cpp

    gui/widget/HeadersWidget/HeadersController.cpp
    gui/widget/HeadersWidget/HeadersView.cpp

    gui/widget/MethodWidget/MethodController.cpp
    gui/widget/MethodWidget/MethodView.cpp

    gui/widget/RawBodyWidget/RawBodyController.cpp
    gui/widget/RawBodyWidget/RawBodyView.cpp

    gui/widget/ResponseHeadersWidget/ResponseHeadersController.cpp
    gui/widget/ResponseHeadersWidget/ResponseHeadersView.cpp

    gui/widget/ResponseRawBodyWidget/ResponseRawBodyController.cpp
    gui/widget/ResponseRawBodyWidget/ResponseRawBodyView.cpp

    gui/widget/UriWidget/UriController.cpp
    gui/widget/UriWidget/UriView.cpp
)

set(HEADERFILES
    domain/body/FormdataRequestBody.hpp
    domain/body/RawRequestBody.hpp

    domain/exception/MethodRequiredException.hpp
    domain/exception/UriRequiredException.hpp

    domain/pipelines/BodyPipeline.hpp
    domain/pipelines/HeadersPipeline.hpp
    domain/pipelines/MethodPipeline.hpp
    domain/pipelines/UriPipeline.hpp

    domain/request/CppRestRequest.hpp

    domain/AfterRequestPipeline.hpp
    domain/BeforeRequestPipeline.hpp
    domain/Request.hpp
    domain/RequestBody.hpp
    domain/RequestData.hpp
    domain/RequestFactory.hpp
    domain/Response.hpp

    gui/MainWindow/MainWindow.hpp
    gui/widget/RequestWidget.hpp
    gui/widget/ResponseWidget.hpp

    gui/widget/CookiesWidget/CookiesController.hpp
    gui/widget/CookiesWidget/CookiesView.hpp
    gui/widget/CookiesWidget/ICookiesView.hpp

    gui/widget/HeadersWidget/HeadersController.hpp
    gui/widget/HeadersWidget/HeadersView.hpp
    gui/widget/HeadersWidget/IHeadersView.hpp

    gui/widget/MethodWidget/IMethodView.hpp
    gui/widget/MethodWidget/MethodController.hpp
    gui/widget/MethodWidget/MethodView.hpp

    gui/widget/RawBodyWidget/RawBodyController.hpp
    gui/widget/RawBodyWidget/RawBodyView.hpp

    gui/widget/ResponseHeadersWidget/ResponseHeadersController.hpp
    gui/widget/ResponseHeadersWidget/ResponseHeadersView.hpp

    gui/widget/ResponseRawBodyWidget/ResponseRawBodyController.hpp
    gui/widget/ResponseRawBodyWidget/ResponseRawBodyView.hpp

    gui/widget/UriWidget/IUriView.hpp
    gui/widget/UriWidget/UriController.hpp
    gui/widget/UriWidget/UriView.hpp

    gui/BeforeWidgetController.hpp
)

add_executable(getit
    ${HEADERFILES}
    ${SOURCEFILES}
    ../resources/resources.qrc
)

# Libraries
target_link_libraries(getit Boost::system)
target_link_libraries(getit cpprest)
target_link_libraries(getit Qt5::Widgets)
