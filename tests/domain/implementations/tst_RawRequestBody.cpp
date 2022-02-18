#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/implementations/RawRequestBody.hpp"

using namespace getit::domain::implementations;

TEST_CASE("RawRequestBody.getContentType")
{
    SECTION("returns the Content-Type set through the constructor")
    {
        // Arrange
        const auto& contentType = "application/json";
        const auto& request = std::make_shared<RawRequestBody>(contentType);

        // Act
        const auto& result = request->getContentType();

        // Assert
        REQUIRE(contentType == result);
    }

    SECTION("returns the default Content-Type when the empty constructor is called")
    {
        // Arrange
        const auto& defaultContentType = "text/plain";
        const auto& request = std::make_shared<RawRequestBody>();

        // Act
        const auto& result = request->getContentType();

        // Assert
        REQUIRE(defaultContentType == result);
    }
}

TEST_CASE("RawRequestBody.getBody")
{
    SECTION("returns the direct string given through setBody")
    {
        // Arrange
        const auto& body = "This is my exact body";
        const auto& request = std::make_shared<RawRequestBody>();

        // Act
        request->setBody(body);
        const auto& result = request->getBody();

        // Assert
        REQUIRE(body == result);
    }

    SECTION("returns the string including linebreaks and tabs exactly as given through setBody")
    {
        // Arrange
        const auto& body = "This is my body\nWith multiple lines\tand a tab for some\treason...";
        const auto& request = std::make_shared<RawRequestBody>();

        // Act
        request->setBody(body);
        const auto& result = request->getBody();

        // Assert
        REQUIRE(body == result);
    }

    SECTION("returns an empty string when the setBody is never called")
    {
        // Arrange
        const auto& request = std::make_shared<RawRequestBody>();

        // Act
        const auto& result = request->getBody();

        // Assert
        REQUIRE(result.empty());
    }
}