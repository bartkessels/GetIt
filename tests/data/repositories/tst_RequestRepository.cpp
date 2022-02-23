#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <cctype>
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