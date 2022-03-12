#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <iomanip>
#include <memory>

#include "data/contracts/RequestRepository.hpp"
#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/repositories/RequestRepository.hpp"
#include "domain/implementations/RawRequestBody.hpp"

using namespace getit::data::repositories;

class RequestRepositoryMock: public getit::data::contracts::RequestRepository
{
    public:
        MAKE_MOCK2(saveRequest, void(const std::string&, std::shared_ptr<getit::domain::models::Request>), override);
        MAKE_MOCK1(loadRequest, (std::shared_ptr<getit::domain::models::Request>(const std::string&)), override);
};

void writeFile(const std::string& path, const std::string& content)
{
    std::ofstream output(path);
    output << std::setw(4) << content << std::endl;
    output.close();
}

TEST_CASE("RequestRepository.saveRequest")
{
    // Before
    const auto& formDataRepository = std::make_shared<RequestRepositoryMock>();
    const auto& rawRepository = std::make_shared<RequestRepositoryMock>();
    const auto& filePath = "./Request.getit";

    const auto& sut = std::make_shared<RequestRepository>(formDataRepository, rawRepository);

    SECTION("calls saveRequest on FormDataRequestRepository when body is instance of FormDataRequestBody")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();
        request->setBody(body);

        // Assert
        REQUIRE_CALL(*formDataRepository, saveRequest(filePath, request));

        // Act
        sut->saveRequest(filePath, request);
    }

    SECTION("calls saveRequest on RawRequestRepository when body is instance of RawRequestBody")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::RawRequestBody>();
        request->setBody(body);

        // Assert
        REQUIRE_CALL(*rawRepository, saveRequest(filePath, request));

        // Act
        sut->saveRequest(filePath, request);
    }

    SECTION("throws a NoAvailableRepositoryException when the body isn't set")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();

        // Act & Assert
        REQUIRE_THROWS_AS(
                sut->saveRequest(filePath, request),
                getit::data::exceptions::NoAvailableRepositoryException
        );
    }

    SECTION("throws a NoAvailableRepositoryException when the body is a nullptr")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();
        request->setBody(nullptr);

        // Act & Assert
        REQUIRE_THROWS_AS(
                sut->saveRequest(filePath, request),
                getit::data::exceptions::NoAvailableRepositoryException
        );
    }
}

TEST_CASE("RequestRepository.loadRequest")
{
    // Before
    const auto& formDataRepository = std::make_shared<RequestRepositoryMock>();
    const auto& rawRepository = std::make_shared<RequestRepositoryMock>();
    const auto& filePath = "./Request.getit";

    const auto& sut = std::make_shared<RequestRepository>(formDataRepository, rawRepository);

    SECTION("calls loadRequest on FormDataRequestRepository when the json contains a form data body")
    {
        // Arrange
        std::string json = R"({"formdata": {}})";
        writeFile(filePath, json);

        // Assert
        REQUIRE_CALL(*formDataRepository, loadRequest(filePath))
            .RETURN(std::make_shared<getit::domain::models::Request>());

        // Act
        sut->loadRequest(filePath);

        // Teardown
        std::remove(filePath);
    }

    SECTION("calls loadRequest on RawRequestRepository when the json contains a raw body")
    {
        // Arrange
        std::string json = R"({"raw": {}})";
        writeFile(filePath, json);

        // Assert
        REQUIRE_CALL(*rawRepository, loadRequest(filePath))
            .RETURN(std::make_shared<getit::domain::models::Request>());

        // Act
        sut->loadRequest(filePath);

        // Teardown
        std::remove(filePath);
    }

    SECTION("throws a NoAvailableRepositoryException when the body isn't set")
    {
        // Arrange
        writeFile(filePath, R"({"uri": "", "method": "GET"})");

        // Act & Assert
        REQUIRE_THROWS_AS(
                sut->loadRequest(filePath),
                getit::data::exceptions::NoAvailableRepositoryException
        );

        // Teardown
        std::remove(filePath);
    }

    SECTION("throws a NoAvailableRepositoryException when the body is a nullptr")
    {
        // Arrange
        writeFile(filePath, R"({"uri": "", "method": "GET"})");

        // Act & Assert
        REQUIRE_THROWS_AS(
                sut->loadRequest(filePath),
                getit::data::exceptions::NoAvailableRepositoryException
        );

        // Teardown
        std::remove(filePath);
    }
}