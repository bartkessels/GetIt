#include <catch2/catch.hpp>
#include <cctype>
#include <memory>

#include "data/repositories/RawRequestRepository.hpp"
#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/RawRequestBody.hpp"

using namespace getit::data::repositories;

void writeRawFile(const std::string& path, const std::string& content)
{
    std::ofstream output(path);
    output << std::setw(4) << content << std::endl;
    output.close();
}


TEST_CASE("RawRequestRepository.saveRequest")
{
    const auto& factory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& repository = std::make_shared<RawRequestRepository>(factory);
    const auto& filePath = "./output.json";

    SECTION("saves all the fields to the specified file")
    {
        // Arrange
        const auto& expectedFileContents = R"({"method":"GET","raw":{"body":"PlainContent","contentType":"text/plain"},"uri":"https://github.com/bartkessels/getit"})";

        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::RawRequestBody>();

        request->setMethod("GET");
        request->setUri("https://github.com/bartkessels/getit");
        request->setBody(body);

        body->setContentType("text/plain");
        body->setBody("PlainContent");

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

TEST_CASE("RawRequestRepository.loadRequest")
{
    const auto& factory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& repository = std::make_shared<RawRequestRepository>(factory);
    const auto& filePath = "./Request.getit";

    SECTION("reads all the fields into the request when it's a raw request")
    {
        // Arrange
        const auto& expectedMethod = "GET";
        const auto& expectedUri = "https://github.com/bartkessels/getit";
        const auto& expectedBody = "This is my raw body";
        const auto& expectedContentType = "text/plain";

        boost::format requestFormat = boost::format(
                R"({"raw":{"body": "%1%", "contentType":"%2%"},"method":"%3%","uri":"%4%"})"
        ) % expectedBody % expectedContentType % expectedMethod % expectedUri;

        writeRawFile(filePath, requestFormat.str());

        // Act
        const auto& actual = repository->loadRequest(filePath);
        const auto& actualBody = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(actual->getBody());

        // Assert
        REQUIRE(actual->getMethod() == expectedMethod);
        REQUIRE(actual->getUri() == expectedUri);
        REQUIRE(actualBody->getContentType() == expectedContentType);
        REQUIRE(actualBody->getBody() == expectedBody);

        std::remove(filePath);
    }
}