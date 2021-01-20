#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <cpprest/http_listener.h>
#include <functional>
#include <memory>

#include "domain/body/RawRequestBody.hpp"
#include "domain/pipelines/BodyPipeline.hpp"
#include "domain/pipelines/HeadersPipeline.hpp"
#include "domain/pipelines/MethodPipeline.hpp"
#include "domain/pipelines/UriPipeline.hpp"
#include "domain/request/CppRestRequest.hpp"
#include "domain/RequestData.hpp"

#include "../../mocks/AfterPipelineMock.hpp"
#include "../../mocks/BeforePipelineMock.hpp"

#include <iostream>

using namespace getit::domain;
using namespace web::http;
using namespace web::http::experimental::listener;

void listen(std::shared_ptr<http_listener> listener, const std::string& method, const std::function<void(http_request)> callback)
{
    listener->support(method, [=](http_request request) {
        callback(request);

        request.reply(status_codes::OK);
    });
}

TEST_CASE("CppRestRequest")
{
    // Before
    const auto& uri = "http://localhost:1874/test_resource";
    const auto& requestListener = std::make_shared<http_listener>(uri);
    requestListener->open().wait();

    SECTION("send executes the registered before pipelines")
    {
        // Arrange
        const auto& methodPipeline = std::make_shared<pipelines::MethodPipeline>("GET");
        const auto& uriPipeline = std::make_shared<pipelines::UriPipeline>(uri);
        const auto& beforePipelineMock = std::make_shared<getit::tests::mocks::BeforePipelineMock>();
        const auto& sut = std::make_unique<request::CppRestRequest>();

        // Register the uri and method pipeline 'cause the
        // RequestData requires the uri and method to have
        // a value
        sut->registerPipeline(methodPipeline);
        sut->registerPipeline(uriPipeline);
        sut->registerPipeline(beforePipelineMock);

        // Assert
        //  execute assert before the call to send 'cause the beforePipeline gets destroyed
        //  when the send method executing finishes
        REQUIRE_CALL(*beforePipelineMock.get(), executeBeforeRequest(ANY(std::shared_ptr<RequestData>)));

        // Act
        sut->send();
    }

    SECTION("send executes the registered after pipelines")
    {
        // Arrange
        const auto& methodPipeline = std::make_shared<pipelines::MethodPipeline>("GET");
        const auto& uriPipeline = std::make_shared<pipelines::UriPipeline>(uri);
        const auto& afterPipelineMock = std::make_shared<getit::tests::mocks::AfterPipelineMock>();
        const auto& sut = std::make_unique<request::CppRestRequest>();

        // Register the uri and method pipeline 'cause the
        // RequestData requires the uri and method to have
        // a value
        sut->registerPipeline(methodPipeline);
        sut->registerPipeline(uriPipeline);
        sut->registerPipeline(afterPipelineMock);

        // Assert, execute assert before the call to send 'cause the beforePipeline gets destroyed
        //         when the send method executing finishes
        REQUIRE_CALL(*afterPipelineMock.get(), executeAfterRequest(ANY(std::shared_ptr<Response>)));

        // Act
        sut->send();
    }

    SECTION("send gives the method from the MethodPipeline straight to the server")
    {
        // Arrange
        const auto& expectedMethod = "GET";
        const auto& methodPipeline = std::make_shared<pipelines::MethodPipeline>(expectedMethod);
        const auto& uriPipeline = std::make_shared<pipelines::UriPipeline>(uri);

        const auto& sut = std::make_unique<request::CppRestRequest>();

        // Register the uri and method pipeline 'cause the
        // RequestData requires the uri and method to have
        // a value
        sut->registerPipeline(methodPipeline);
        sut->registerPipeline(uriPipeline);

        // Assert
        listen(requestListener, methods::GET, [=](http_request request) {
            REQUIRE(expectedMethod == request.method());
        });

        // Act
        sut->send();
    }

    SECTION("send gives the body from the BodyPipeline straight to the server")
    {
        // Arrange
        const auto& expectedBodyValue = "This is my raw request body";
        const auto& body = std::make_shared<body::RawRequestBody>();
        body->setBody(expectedBodyValue);

        const auto& methodPipeline = std::make_shared<pipelines::MethodPipeline>("POST");
        const auto& uriPipeline = std::make_shared<pipelines::UriPipeline>(uri);
        const auto& bodyPipeline = std::make_shared<pipelines::BodyPipeline>(body);

        const auto& sut = std::make_unique<request::CppRestRequest>();

        // Register the uri and method pipeline 'cause the
        // RequestData requires the uri and method to have
        // a value
        sut->registerPipeline(methodPipeline);
        sut->registerPipeline(uriPipeline);
        sut->registerPipeline(bodyPipeline);

        // Assert
        listen(requestListener, methods::POST, [=](http_request request) {
            REQUIRE(expectedBodyValue == request.extract_string().get());
        });

        // Act
        sut->send();
    }

    SECTION("send gives the headers from the HeaderPipeline straight to the server")
    {
        
        // Arrange
        const auto& expectedHeaderKey = "Accept-Language";
        const auto& expectedHeaderValue = "EN";

        const auto& methodPipeline = std::make_shared<pipelines::MethodPipeline>("GET");
        const auto& uriPipeline = std::make_shared<pipelines::UriPipeline>(uri);
        const auto& headersPipeline = std::make_shared<pipelines::HeadersPipeline>();

        headersPipeline->addHeader(expectedHeaderKey, expectedHeaderValue);

        const auto& sut = std::make_unique<request::CppRestRequest>();

        // Register the uri and method pipeline 'cause the
        // RequestData requires the uri and method to have
        // a value
        sut->registerPipeline(methodPipeline);
        sut->registerPipeline(uriPipeline);
        sut->registerPipeline(headersPipeline);

        // Assert
        listen(requestListener, methods::GET, [=](http_request request) {
            REQUIRE_FALSE(request.headers().empty());

            bool foundHeader = false;

            for (const auto& [header, value] : request.headers()) {
                if (header == expectedHeaderKey) {
                    foundHeader = true;
                    REQUIRE(expectedHeaderValue == value);
                }
            }

            REQUIRE(foundHeader);
        });

        // Act
        sut->send();
    }

    // After
    requestListener->close().wait();
}