#include <boost/format.hpp>
#include <catch2/catch.hpp>
#include <filesystem>
#include <memory>
#include <string>

#include "domain/implementations/FormDataRequestBody.hpp"

using namespace getit::domain::implementations;

TEST_CASE("FormDataRequestBody.getContentType")
{
    const auto& boundary = "--boundary-";
    const auto& body = std::make_shared<FormDataRequestBody>(boundary);

    SECTION("returns the expected multipart/form-data Content-Type with the given boundary")
    {
        // Arrange
        const auto& expectedContentType = (boost::format(
            "multipart/form-data; boundary=\"%1%\""
        ) % boundary).str();

        // Act
        const auto& result = body->getContentType();

        // Assert
        REQUIRE(expectedContentType == result);
    }
}

TEST_CASE("FormDataRequestBody.getBody")
{
    const auto& boundary = "--boundary-";
    const auto& body = std::make_shared<FormDataRequestBody>(boundary);

    SECTION("returns the string with unescaped characters for elements")
    {
        // Arrange
        const auto& key = "element";
        const auto& value = "P@ssW0rd!\"";
        const auto& expectedBody = (boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n\r\n--%1%--\r\n"
        ) % boundary % key % value).str();

        // Act
        body->addElement(key, value);
        const auto& result = body->getBody();

        // Assert
        REQUIRE(expectedBody == result);
    }

    SECTION("returns the expected format for elements when one element is set")
    {
        // Arrange
        const auto& key = "element";
        const auto& value = "value";
        const auto& expectedBody = (boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n\r\n--%1%--\r\n"
        ) % boundary % key % value).str();

        // Act
        body->addElement(key, value);
        const auto& result = body->getBody();

        // Assert
        REQUIRE(expectedBody == result);
    }

    SECTION("returns the expected format for elements when multiple elements are set")
    {
        // Arrange
        const auto& key1 = "element_1";
        const auto& value1 = "value_1";
        const auto& key2 = "element_2";
        const auto& value2 = "value_2";
        const auto& key3 = "element_3";
        const auto& value3 = "value_3";

        const auto& elementTemplate = "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n";

        const auto& expectedBody = (boost::format("%1%%2%%3%%4%")
            % (boost::format(elementTemplate) % boundary % key1 % value1).str()
            % (boost::format(elementTemplate) % boundary % key2 % value2).str()
            % (boost::format(elementTemplate) % boundary % key3 % value3).str()
            % (boost::format("\r\n--%1%--\r\n") % boundary).str()
        ).str();

        // Act
        body->addElement(key1, value1);
        body->addElement(key2, value2);
        body->addElement(key3, value3);

        const auto& result = body->getBody();

        // Assert
        REQUIRE(expectedBody == result);
    }

    SECTION("returns the expected format for files when one file is set")
    {
        // Arrange
        const auto& key = "element";
        const auto& filePath = "./bin/test_file.txt";
        const auto& fileContents = "content";
        const auto& expectedBody = (boost::format(
            "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n%4%\r\n\r\n--%1%--\r\n"
        ) % boundary % key % filePath % fileContents).str();

        // Act
        body->addFile(key, filePath);
        const auto& result = body->getBody();

        // Assert
        REQUIRE(expectedBody == result);
    }

    SECTION("returns the expected format for files when multiple files are set")
    {
        // Arrange
        const auto& key1 = "element_1";
        const auto& key2 = "element_2";
        const auto& key3 = "element_3";
        const auto& filePath = "./bin/test_file.txt";
        const auto& fileContents = "content";

        const auto& fileTemplate = "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n%4%\r\n";

        const auto& expectedBody = (boost::format("%1%%2%%3%%4%")
            % (boost::format(fileTemplate) % boundary % key1 % filePath % fileContents).str()
            % (boost::format(fileTemplate) % boundary % key2 % filePath % fileContents).str()
            % (boost::format(fileTemplate) % boundary % key3 % filePath % fileContents).str()
            % (boost::format("\r\n--%1%--\r\n") % boundary).str()
        ).str();

        // Act
        body->addFile(key1, filePath);
        body->addFile(key2, filePath);
        body->addFile(key3, filePath);

        const auto& result = body->getBody();

        // Assert
        REQUIRE(expectedBody == result);
    }

    SECTION("returns the expected format for both elements and files when both are set")
    {
        // Arrange
        const auto& fileKey1 = "element_1";
        const auto& fileKey2 = "element_2";
        const auto& fileKey3 = "element_3";
        const auto& key1 = "element_1";
        const auto& value1 = "value_1";
        const auto& key2 = "element_2";
        const auto& value2 = "value_2";
        const auto& key3 = "element_3";
        const auto& value3 = "value_3";
        const auto& filePath = "./bin/test_file.txt";
        const auto& fileContents = "content";

        const auto& elementTemplate = "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"\r\n\r\n%3%\r\n";
        const auto& fileTemplate = "--%1%\r\nContent-Disposition: form-data; name=\"%2%\"; filename=\"%3%\"\r\n\r\n%4%\r\n";

        const auto& expectedBody = (boost::format("%1%%2%%3%%4%%5%%6%%7%")
            % (boost::format(elementTemplate) % boundary % key1 % value1).str()
            % (boost::format(elementTemplate) % boundary % key2 % value2).str()
            % (boost::format(elementTemplate) % boundary % key3 % value3).str()
            % (boost::format(fileTemplate) % boundary % fileKey1 % filePath % fileContents).str()
            % (boost::format(fileTemplate) % boundary % fileKey2 % filePath % fileContents).str()
            % (boost::format(fileTemplate) % boundary % fileKey3 % filePath % fileContents).str()
            % (boost::format("\r\n--%1%--\r\n") % boundary).str()
        ).str();

        // Act
        body->addElement(key1, value1);
        body->addElement(key2, value2);
        body->addElement(key3, value3);

        body->addFile(fileKey1, filePath);
        body->addFile(fileKey2, filePath);
        body->addFile(fileKey3, filePath);

        const auto& result = body->getBody();

        // Assert
        REQUIRE(expectedBody == result);
    }
}

TEST_CASE("FormDataRequestBody.setElements")
{
    const auto& boundary = "--boundary-";
    const auto& body = std::make_shared<FormDataRequestBody>(boundary);

    SECTION("overwrites the previous set elements through addElement")
    {
        // Arrange
        std::map<std::string, std::string> oldElements = {
            { "username", "someone" },
            { "password", "TopSecret!" }
        };
        std::map<std::string, std::string> newElements = {
            { "token", "81b9ef1d-e5ea-41d9-bdb8-ee08296a59e8" },
            { "refresh-token", "5c8b8ab1-411c-4ff8-a2d6-b97623586364" }
        };

        for (const auto& [key, value] : oldElements) {
            body->addElement(key, value);
        }

        // Act
        body->setElements(newElements);

        // Assert
        REQUIRE(oldElements != body->getElements());
        REQUIRE(newElements == body->getElements());
    }
}

TEST_CASE("FormDataRequestBody.setFiles")
{
    const auto& boundary = "--boundary-";
    const auto& body = std::make_shared<FormDataRequestBody>(boundary);

    SECTION("overwrites the previous set elements through addFile")
    {
        // Arrange
        std::map<std::string, std::string> oldFiles = {
            { "image", "./a-butterfly.png" },
            { "resume", "./please-hire-me-resume.odt" }
        };
        std::map<std::string, std::string> newFiles = {
            { "profile-picture", "../images/happy-me.png" },
            { "passport", "../images/personal/passport_scan.png" }
        };

        for (const auto& [key, value] : oldFiles) {
            body->addFile(key, value);
        }

        // Act
        body->setFiles(newFiles);

        // Assert
        REQUIRE(oldFiles != body->getFiles());
        REQUIRE(newFiles == body->getFiles());
    }
}

TEST_CASE("FormDataRequestBody.setBoundary")
{
    SECTION("overwrites the previous set boundary through the constructor")
    {
        // Arrange
        const auto& oldBoundary = "--old-boundary-";
        const auto& newBoundary = "--new-boundary-";
        const auto& body = std::make_shared<FormDataRequestBody>(oldBoundary);

        // Act
        body->setBoundary(newBoundary);

        // Assert
        REQUIRE(oldBoundary != body->getBoundary());
        REQUIRE(newBoundary == body->getBoundary());
    }
}
