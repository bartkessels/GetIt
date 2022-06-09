#include <catch2/catch.hpp>
#include <map>
#include <memory>
#include <string>
#include <tuple>

#include "domain/models/Request.hpp"
#include "domain/models/Variable.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/transformations/VariablesTransformation.hpp"

using namespace getit::domain::models;
using namespace getit::domain::implementations;
using namespace getit::domain::transformations;

#include <iostream>

TEST_CASE("VariablesTransformation.transform")
{
    SECTION("replaces all variables in the uri")
    {
        // Arrange
        const auto& expectedUri = "http://hostname.local/image.png";
        std::list<std::shared_ptr<Variable>> variables = {
            std::make_shared<Variable>("scheme", "http://"),
            std::make_shared<Variable>("file", "image.png")
        };

        const auto& request = std::make_shared<Request>();
        request->setUri("{scheme}hostname.local/{file}");

        const auto& sut = std::make_unique<VariablesTransformation>(variables);

        // Act
        const auto& result = sut->transform(request);

        // Assert
        REQUIRE(expectedUri == result->getUri());
    }

    SECTION("replaces all variables in the form data request body elements")
    {
        // Arrange
        std::map<std::string, std::string> expectedElements = {
            { "password", "Top!Secret" },
            { "username", "someone" }
        };

        std::list<std::shared_ptr<Variable>> variables = {
            std::make_shared<Variable>("element1", "password"),
            std::make_shared<Variable>("username", "someone")
        };

        const auto& request = std::make_shared<Request>();
        const auto& body = std::make_shared<FormDataRequestBody>();
        body->addElement("{element1}", "Top!Secret");
        body->addElement("username", "{username}");

        request->setBody(body);

        const auto& sut = std::make_unique<VariablesTransformation>(variables);

        // Act
        const auto& result = sut->transform(request);
        const auto& resultBody = std::dynamic_pointer_cast<FormDataRequestBody>(result->getBody());

        // Assert
        REQUIRE(expectedElements == resultBody->getElements());
    }

    SECTION("replaces all variables in the form data request body files")
    {
        // Arrange
        std::map<std::string, std::string> expectedFiles = {
            { "biography", "./bio.txt" },
            { "picture", "./images/me/hi.png" }
        };

        std::list<std::shared_ptr<Variable>> variables = {
            std::make_shared<Variable>("element1", "biography"),
            std::make_shared<Variable>("image-path", "./images/me/hi.png")
        };

        const auto& request = std::make_shared<Request>();
        const auto& body = std::make_shared<FormDataRequestBody>();
        body->addFile("{element1}", "./bio.txt");
        body->addFile("picture", "{image-path}");

        request->setBody(body);

        const auto& sut = std::make_unique<VariablesTransformation>(variables);

        // Act
        const auto& result = sut->transform(request);
        const auto& resultBody = std::dynamic_pointer_cast<FormDataRequestBody>(result->getBody());

        // Assert
        REQUIRE(expectedFiles == resultBody->getFiles());
    }

    SECTION("replaces all variables in the raw request body")
    {
        // Arrange
        const auto& expectedBody = "This is my expected body!";

        std::list<std::shared_ptr<Variable>> variables = {
            std::make_shared<Variable>("intro", "This is"),
            std::make_shared<Variable>("end", "expected body!")
        };

        const auto& request = std::make_shared<Request>();
        const auto& body = std::make_shared<RawRequestBody>();
        body->setBody("{intro} my {end}");

        request->setBody(body);

        const auto& sut = std::make_unique<VariablesTransformation>(variables);

        // Act
        const auto& result = sut->transform(request);

        // Assert
        REQUIRE(expectedBody == result->getBody()->getBody());
    }

    SECTION("replaces all variables in the raw request body content type")
    {
        // Arrange
        const auto& expectedContentType = "application/json";

        std::list<std::shared_ptr<Variable>> variables = {
            std::make_shared<Variable>("specific-type", "json")
        };

        const auto& request = std::make_shared<Request>();
        const auto& body = std::make_shared<RawRequestBody>();
        body->setContentType("application/{specific-type}");

        request->setBody(body);

        const auto& sut = std::make_unique<VariablesTransformation>(variables);

        // Act
        const auto& result = sut->transform(request);
        const auto& resultBody = std::dynamic_pointer_cast<FormDataRequestBody>(result->getBody());

        // Assert
        REQUIRE(expectedContentType == result->getBody()->getContentType());
    }

    SECTION("replaces all variables in the headers")
    {
        // Arrange
        std::map<std::string, std::string> expectedHeaders = {
            { "Accept-Language", "en-US" },
            { "Content-Type", "application/json" }
        };

        std::list<std::shared_ptr<Variable>> variables = {
            std::make_shared<Variable>("header1", "Accept-Language"),
            std::make_shared<Variable>("content-type", "application/json")
        };

        const auto& request = std::make_shared<Request>();
        request->addHeader("{header1}", "en-US");
        request->addHeader("Content-Type", "{content-type}");

        const auto& sut = std::make_unique<VariablesTransformation>(variables);

        // Act
        const auto& result = sut->transform(request);

        // Assert
        REQUIRE(expectedHeaders == result->getHeaders());
    }
}