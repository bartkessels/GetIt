#include <catch2/catch.hpp>
#include <cpprest/http_listener.h>
#include <memory>
#include <utility>

#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
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

    SECTION("adds the uri to the request")
    {
        // Arrange
        request->setMethod("GET");
        request->setUri(uri);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            /// If the control flow comes here, it means that the request is
            /// sent to the uri of the listener (i.e. the uri that's also set
            /// on the request)
            REQUIRE(true);
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
            REQUIRE(actualRequest.body().read().get() <= 0);
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
            REQUIRE(actualRequest.body().read().get() <= 0);
        });

        // Act
        sut->send(request).wait();
    }

    SECTION("does add a body to the request when body is of type form data")
    {
        // Arrange
        const auto& key = "email_address";
        const auto& value = "my_first_email@localhost";

        const auto& fileKey = "picture.png";
        const auto& filePath = "./test_file.txt";
        const auto& fileContent = "content";

        const auto& body = std::make_shared<implementations::FormDataRequestBody>();
        body->addElement(key, value);
        body->addFile(fileKey, filePath);

        request->setMethod("GET");
        request->setUri(uri);
        request->setBody(body);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            REQUIRE(actualRequest.to_string().find(key));
            REQUIRE(actualRequest.to_string().find(value));

            REQUIRE(actualRequest.to_string().find(fileKey));
            REQUIRE(actualRequest.to_string().find(filePath));
            REQUIRE(actualRequest.to_string().find(fileContent));
        });

        // Act
        sut->send(request).wait();
    }

    SECTION("does add a body to the request when body is of type raw")
    {
        // Arrange
        auto bodyContent = "This is my plain text raw body";

        const auto& body = std::make_shared<implementations::RawRequestBody>();
        body->setBody(bodyContent);

        request->setMethod("GET");
        request->setUri(uri);
        request->setBody(body);

        // Assert
        listen(requestListener, [=](const http_request& actualRequest) {
            REQUIRE(actualRequest.to_string().find(bodyContent));
        });

        // Act
        sut->send(request).wait();
    }
}