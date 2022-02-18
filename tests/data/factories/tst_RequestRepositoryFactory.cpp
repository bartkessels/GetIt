#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <memory>

#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/factories/RequestRepositoryFactory.hpp"
#include "data/repositories/FormdataRequestRepository.hpp"
#include "data/repositories/RawRequestRepository.hpp"
#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/FormdataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"

using namespace getit::data::factories;

class RequestMock: public getit::domain::models::Request
{
    public:
        MAKE_MOCK0(getBody, std::shared_ptr<getit::domain::models::RequestBody>());
};

TEST_CASE("RequestRepositoryFactory.getRepository")
{
    const auto& requestFactory = std::make_shared<getit::domain::factories::RequestFactory>();
    const auto& factory = std::make_shared<RequestRepositoryFactory>(requestFactory);

    SECTION("returns an instance of FormdataRequestRepository when request is an instance of FormdataRequestBody")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormdataRequestBody>();

        request->setBody(body);

        // Act
        const auto& result = factory->getRepository(request);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::data::repositories::FormdataRequestRepository>(result));
    }

    SECTION("returns an instance of RawRequestRepository when request is an instance of RawRequestBody")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::RawRequestBody>();

        request->setBody(body);

        // Act
        const auto& result = factory->getRepository(request);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::data::repositories::RawRequestRepository>(result));
    }

    SECTION("throws an NoAvailableRepositoryException when the request isn't an instance of FormdataRequestBody or RawRequestBody")
    {
        // Assert
        const auto& request = std::make_shared<RequestMock>();

        // Act & Assert
        REQUIRE_THROWS_AS(
            factory->getRepository(request),
            getit::data::exceptions::NoAvailableRepositoryException
        );
    }
}