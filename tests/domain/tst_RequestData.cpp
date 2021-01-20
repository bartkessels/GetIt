#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/body/FormdataRequestBody.hpp"
#include "domain/body/RawRequestBody.hpp"
#include "domain/RequestData.hpp"

using namespace getit::domain;

TEST_CASE("RequestData")
{
    SECTION("getMethod returns the method given through setMethod")
    {
        // Arrange
        std::string method = "GET";
        
        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->setMethod(method);

        // Assert
        REQUIRE(sut->getMethod() == method);
    }

    SECTION("getMethod throws an exception when an empty string is given through setMethod")
    {
        // Arrange
        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->setMethod("");
        
        // Assert
        REQUIRE_THROWS(sut->getMethod());
    }

    SECTION("getMethod throws an exception when no method is set")
    {
        // Arrange
        const auto& sut = std::make_unique<RequestData>();

        // Act & Assert
        REQUIRE_THROWS(sut->getMethod());
    }
    SECTION("getUri returns the uri given through setUri")
    {
        // Arrange
        std::string uri = "https://bartkessels.net";
        
        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->setUri(uri);

        // Assert
        REQUIRE(sut->getUri() == uri);
    }

    SECTION("getUri throws an exception when an empty string is given through setUri")
    {
        // Arrange
        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->setUri("");
        
        // Assert
        REQUIRE_THROWS(sut->getUri());
    }

    SECTION("getUri throws an exception when no uri is set")
    {
        // Arrange
        const auto& sut = std::make_unique<RequestData>();

        // Act & Assert
        REQUIRE_THROWS(sut->getUri());
    }

    SECTION("getHeaders returns the headers that are set using addOrUpdateHeader")
    {
        // Arrange
        std::string header1 = "h1";
        std::string header2 = "h2";
        std::map<std::string, std::string> expectedHeaders = {
            {header1, ""},
            {header2, ""}
        };

        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->addOrUpdateHeader(header1, "");
        sut->addOrUpdateHeader(header2, "");

        // Assert
        REQUIRE(sut->getHeaders() == expectedHeaders);
    }

    SECTION("getHeaders returns an empty map when no headers are set using addOrUpdateHeader")
    {
        // Arrange
        const auto& sut = std::make_unique<RequestData>();

        // Assert
        REQUIRE(sut->getHeaders().empty());
    }

    SECTION("getBody returns the FormdataRequestBody when that object is given through setBody")
    {
        // Arrange
        const auto& requestBody = std::make_shared<body::FormdataRequestBody>("boundary");

        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->setBody(requestBody);

        // Assert
        REQUIRE(dynamic_cast<body::FormdataRequestBody*>(sut->getBody().get()));
    }

    SECTION("getBody returns the RawRequestBody when that object is given through setBody")
    {
        // Arrange
        const auto& requestBody = std::make_shared<body::RawRequestBody>();

        const auto& sut = std::make_unique<RequestData>();

        // Act
        sut->setBody(requestBody);

        // Assert
        REQUIRE(dynamic_cast<body::RawRequestBody*>(sut->getBody().get()));
    }

    SECTION("getBody returns a nullptr when no body set using setBody")
    {
        // Arrange
        const auto& sut = std::make_unique<RequestData>();

        // Assert
        REQUIRE(sut->getBody() == nullptr);
    }
}