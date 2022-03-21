#include <catch2/catch.hpp>
#include <map>
#include <memory>
#include <string>

#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"

using namespace getit::domain::factories;

TEST_CASE("RequestFactory.getRequest [RawRequestBody - body overload]")
{
    const auto& factory = std::make_shared<RequestFactory>();
    const auto& method = "POST";
    const auto& uri = "https://github.com/bartkessels";
    const auto& headers = std::map<std::string, std::string>();

    SECTION("returns an instance of RawRequestBody when using the overload with body")
    {
        // Arrange
        const auto& body = "This is my raw body";
        const auto& contentType = "text/plain";

        // Act
        const auto& result = factory->getRequest(method, uri, headers, body, contentType);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(result->getBody()));
    }

    SECTION("returns an instance of RawRequestBody with the correct values set for just the body")
    {
        // Arrange
        const auto& body = "This is my raw body";

        // Act
        const auto& result = factory->getRequest(method, uri, headers, body);
        const auto& requestBody = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(result->getBody());

        // Assert
        REQUIRE(body == requestBody->getBody());
    }
}

TEST_CASE("RequestFactory.getRequest [RawRequestBody - body/contentType overload")
{
    const auto& factory = std::make_shared<RequestFactory>();
    const auto& method = "POST";
    const auto& uri = "https://github.com/bartkessels";
    const auto& headers = std::map<std::string, std::string>();
    
    SECTION("returns an instance of RawRequestBody when using the overload with body and contentType")
    {
        // Arrange
        const auto& body = "This is my raw body";
        const auto& contentType = "text/plain";

        // Act
        const auto& result = factory->getRequest(method, uri, headers, body, contentType);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(result->getBody()));
    }

    SECTION("returns an instance of RawRequestBody with the correct values set")
    {
        // Arrange
        const auto& body = "This is my raw body";
        const auto& contentType = "text/plain";

        // Act
        const auto& result = factory->getRequest(method, uri, headers, body, contentType);
        const auto& requestBody = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(result->getBody());

        // Assert
        REQUIRE(body == requestBody->getBody());
        REQUIRE(contentType == requestBody->getContentType());
    }
}

TEST_CASE("RequestFactory.getRequest [FormDataRequestBody]")
{
    const auto& factory = std::make_shared<RequestFactory>();
    const auto& method = "POST";
    const auto& uri = "https://github.com/bartkessels";
    const auto& headers = std::map<std::string, std::string>();

    SECTION("returns an instance of FormDataRequestBody when using the overload with elements, files and boundary")
    {
        // Arrange
        std::map<std::string, std::string> elements = { { "username", "bartkessels" } };
        std::map<std::string, std::string> files = { { "image", "./butterfly.png" } };
        const auto& boundary = "--boundary";

        // Act
        const auto& result = factory->getRequest(method, uri, headers, elements, files, boundary);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(result->getBody()));
    }

    SECTION("returns an instance of FormDataRequestBody with the correct values set")
    {
        // Arrange
        std::map<std::string, std::string> elements = { { "username", "bartkessels" } };
        std::map<std::string, std::string> files = { { "image", "./butterfly.png" } };
        const auto& boundary = "--boundary";

        // Act
        const auto& result = factory->getRequest(method, uri, headers, elements, files, boundary);
        const auto& requestBody = std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(result->getBody());

        // Assert
        REQUIRE(elements == requestBody->getElements());
        REQUIRE(files == requestBody->getFiles());
    }
}