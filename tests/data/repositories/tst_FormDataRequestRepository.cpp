#include <catch2/catch.hpp>
#include <cctype>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <regex>

#include "data/repositories/FormDataRequestRepository.hpp"
#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"

using namespace getit::data::repositories;

TEST_CASE("FormDataRequestRepository.saveRequest")
{
    const auto& factory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& repository = std::make_shared<FormDataRequestRepository>(factory);
    const auto& filePath = "./output.json";

    SECTION("saves all the fields to the specified file")
    {
        // Arrange
        const auto& expectedFileContents = R"({"formdata":{"boundary":"--bound","elements":[],"files":[]},"method":"GET","uri":"https://github.com/bartkessels/getit"})";

        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();
        request->setMethod("GET");
        request->setUri("https://github.com/bartkessels/getit");
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
        const auto& expectedFileContents = R"({"formdata":{"boundary":"--bound","elements":[{"key":"password","value":"password"},{"key":"username","value":"someone"}],"files":[]},"method":"GET","uri":"https://github.com/bartkessels/getit"})";

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
        const auto& expectedFileContents = R"({"formdata":{"boundary":"--bound","elements":[],"files":[{"filePath":"./picture.png","key":"image"},{"filePath":"./test_file.txt","key":"test"}]},"method":"GET","uri":"https://github.com/bartkessels/getit"})";

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
}