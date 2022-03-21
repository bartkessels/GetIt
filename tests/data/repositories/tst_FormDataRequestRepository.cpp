#include <catch2/catch.hpp>
#include <cctype>
#include <fstream>
#include <memory>
#include <string>

#include "data/repositories/FormDataRequestRepository.hpp"
#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"

#include <iostream>
using namespace getit::data::repositories;

void writeFormDataFile(const std::string& path, const std::string& content)
{
    std::ofstream output(path);
    output << std::setw(4) << content << std::endl;
    output.close();
}

TEST_CASE("FormDataRequestRepository.saveRequest")
{
    const auto& factory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& repository = std::make_shared<FormDataRequestRepository>(factory);
    const auto& filePath = "./Request.getit";

    SECTION("saves all the fields to the specified file")
    {
        // Arrange
        const auto& expectedFileContents = R"({"formdata":{"boundary":"--bound","elements":[],"files":[]},"headers":[{"header":"Content-Type","value":"application/json"}],"method":"GET","uri":"https://github.com/bartkessels/getit"})";

        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();
        request->setMethod("GET");
        request->setUri("https://github.com/bartkessels/getit");
        request->addHeader("Content-Type", "application/json");
        request->setBody(body);
        body->setBoundary("--bound");

        // Act
        repository->saveRequest(filePath, request);

        // Assert
        std::ifstream input(filePath);
        std::string fileContents(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>())
        );
        
        fileContents.erase(std::remove_if(
            fileContents.begin(), fileContents.end(), ::isspace
        ), fileContents.end());
        
        REQUIRE(expectedFileContents == fileContents);

        std::remove(filePath);
    }

    SECTION("saves all the elements")
    {
        // Arrange
        const auto& expectedFileContents = R"({"formdata":{"boundary":"--bound","elements":[{"key":"password","value":"password"},{"key":"username","value":"someone"}],"files":[]},"headers":[],"method":"GET","uri":"https://github.com/bartkessels/getit"})";

        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();
        request->setMethod("GET");
        request->setUri("https://github.com/bartkessels/getit");
        request->setBody(body);
        body->setBoundary("--bound");
        body->addElement("username", "someone");
        body->addElement("password", "password");

        // Act
        repository->saveRequest(filePath, request);

        // Assert
        std::ifstream input(filePath);
        std::string fileContents(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>())
        );
        
        fileContents.erase(std::remove_if(
            fileContents.begin(), fileContents.end(), ::isspace
        ), fileContents.end());
        
        REQUIRE(expectedFileContents == fileContents);

        std::remove(filePath);
    }

    SECTION("saves all the file paths")
    {
        // Arrange
        const auto& expectedFileContents = R"({"formdata":{"boundary":"--bound","elements":[],"files":[{"filePath":"./picture.png","key":"image"},{"filePath":"./test_file.txt","key":"test"}]},"headers":[],"method":"GET","uri":"https://github.com/bartkessels/getit"})";

        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();
        request->setMethod("GET");
        request->setUri("https://github.com/bartkessels/getit");
        request->setBody(body);
        body->setBoundary("--bound");
        body->addFile("image", "./picture.png");
        body->addFile("test", "./test_file.txt");

        // Act
        repository->saveRequest(filePath, request);

        // Assert
        std::ifstream input(filePath);
        std::string fileContents(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>())
        );
        
        fileContents.erase(std::remove_if(
            fileContents.begin(), fileContents.end(), ::isspace
        ), fileContents.end());
        
        REQUIRE(expectedFileContents == fileContents);

        std::remove(filePath);
    }

    SECTION("saves all the headers")
    {
        // Arrange
        const auto& expectedFileContents = R"({"formdata":{"boundary":"","elements":[],"files":[]},"headers":[{"header":"Accept-Language","value":"nl-NL"},{"header":"Content-Type","value":"application/json"}],"method":"GET","uri":"https://github.com/bartkessels/getit"})";

        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();
        request->setMethod("GET");
        request->setUri("https://github.com/bartkessels/getit");
        request->setBody(body);
        request->addHeader("Content-Type", "application/json");
        request->addHeader("Accept-Language", "nl-NL");

        // Act
        repository->saveRequest(filePath, request);

        // Assert
        std::ifstream input(filePath);
        std::string fileContents(
                (std::istreambuf_iterator<char>(input)),
                (std::istreambuf_iterator<char>())
        );

        fileContents.erase(std::remove_if(
                fileContents.begin(), fileContents.end(), ::isspace
        ), fileContents.end());

        REQUIRE(expectedFileContents == fileContents);

        std::remove(filePath);
    }
}

TEST_CASE("FormDataRequestRepository.loadRequest")
{
    const auto& factory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& repository = std::make_shared<FormDataRequestRepository>(factory);
    const auto& filePath = "./Request.getit";

    SECTION("reads all the fields into the request when it's a form data request")
    {
        // Arrange
        const auto& expectedMethod = "GET";
        const auto& expectedUri = "https://github.com/bartkessels/getit";
        const auto& expectedHeader = "Content-Type";
        const auto& expectedHeaderValue = "application/json";
        const auto& expectedBoundary = "--bound";
        const auto& expectedKey = "key";
        const auto& expectedValue = "value";
        const auto& expectedFileName = "image.png";
        const auto& expectedFilePath = "./bin/tst_file.txt";

        boost::format requestFormat = boost::format(
                R"({"formdata":{"boundary":"%1%","elements":[{"key":"%2%","value":"%3%"}],"files":[{"key":"%4%","filePath":"%5%"}]},"headers":[{"header":"%6%","value":"%7%"}],"method":"%8%","uri":"%9%"})"
        ) % expectedBoundary % expectedKey % expectedValue % expectedFileName % expectedFilePath % expectedHeader % expectedHeaderValue % expectedMethod % expectedUri;

        writeFormDataFile(filePath, requestFormat.str());

        // Act
        const auto& actual = repository->loadRequest(filePath);
        const auto& actualBody = std::dynamic_pointer_cast<getit::domain::implementations::FormDataRequestBody>(actual->getBody());

        // Assert
        REQUIRE(actual->getMethod() == expectedMethod);
        REQUIRE(actual->getUri() == expectedUri);
        std::cout << actual->getHeaders().find(expectedHeader)->first << std::endl;
        std::cout << actual->getHeaders().find(expectedHeader)->second << std::endl;
        REQUIRE(actual->getHeaders().find(expectedHeader)->first == expectedHeader);
        REQUIRE(actual->getHeaders().find(expectedHeader)->second == expectedHeaderValue);
        REQUIRE(actualBody->getBoundary() == expectedBoundary);
        REQUIRE(actualBody->getElements().find(expectedKey)->first == expectedKey);
        REQUIRE(actualBody->getElements().find(expectedKey)->second == expectedValue);
        REQUIRE(actualBody->getFiles().find(expectedFileName)->first == expectedFileName);
        REQUIRE(actualBody->getFiles().find(expectedFileName)->second == expectedFilePath);

        std::remove(filePath);
    }
}