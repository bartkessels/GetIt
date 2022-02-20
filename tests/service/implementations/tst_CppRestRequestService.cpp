#include <catch2/catch.hpp>
#include <cpprest/http_listener.h>
#include <memory>
#include <utility>

#include "domain/implementations/FormdataRequestBody.hpp"
#include "domain/models/Request.hpp"
#include "service/implementations/CppRestRequestService.hpp"

using namespace getit::domain;
using namespace getit::service::implementations;
using namespace web::http;
using namespace web::http::experimental::listener;

void listen(const std::shared_ptr<http_listener>& listener, const std::function<void(http_request)>& callback)
{
    listener->support([=](const auto& request) {
        callback(request);
        request.reply(status_codes::OK);
    });
}

TEST_CASE("CppRestRequestService.send")
{
    const auto& sut = std::make_shared<CppRestRequestService>();
    const auto& request = std::make_shared<models::Request>();

    // Setup request listener
    const auto& uri = "http://localhost:1874/test_resource";
    const auto& requestListener = std::make_shared<http_listener>(uri);
    requestListener->open().wait();

    SECTION("adds the method to the request")
    {
        // Arrange
        const auto& expectedMethod = "PUT";

        request->setMethod(expectedMethod);
        request->setUri(uri);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            REQUIRE(actualRequest.method() == expectedMethod);
        });

        // Act
        sut->send(request).wait();
    }

    SECTION("adds the headers to the request")
    {
        // Arrange
        std::map<std::string, std::string> expectedHeaders = {
                { "Content-Type", "application/json" },
                { "Accept-Language", "en-US" }
        };

        request->setMethod("GET");
        request->setUri(uri);
        request->setHeaders(expectedHeaders);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            for (auto [header, value] : expectedHeaders) {
                REQUIRE(actualRequest.headers().match(header, value));
            }
        });

        // Act
        sut->send(request).wait();
    }

    SECTION("does not add a body to the request when no body is set")
    {
        // Arrange
        request->setMethod("GET");
        request->setUri(uri);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            // TODO: Implement check if the body is empty
        });

        // Act
        sut->send(request).wait();
    }

    SECTION("does not add a body to the request when body points to null")
    {
        // Arrange
        request->setMethod("GET");
        request->setUri(uri);
        request->setBody(nullptr);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            // TODO: Implement check if the body is empty
        });

        // Act
        sut->send(request).wait();
    }

    SECTION("does add a body to the request when body is of type form data")
    {
        // Arrange
        const auto& body = std::make_shared<implementations::FormdataRequestBody>();
        body->addElement("key", "value");

        request->setMethod("GET");
        request->setUri(uri);
        request->setBody(body);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            // TODO: Implement check if the body contains the elements from the body
        });

        // Act
        sut->send(request).wait();
    }

    // adds a formdata body to the request
    // adds a raw body to the request
}