#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <memory>

#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/factories/RequestRepositoryFactory.hpp"
#include "data/repositories/FormDataRequestRepository.hpp"
#include "data/repositories/RawRequestRepository.hpp"
#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"
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

    SECTION("returns an instance of FormDataRequestRepository when request is an instance of FormDataRequestBody")
    {
        // Arrange
        const auto& request = std::make_shared<getit::domain::models::Request>();
        const auto& body = std::make_shared<getit::domain::implementations::FormDataRequestBody>();

        request->setBody(body);

        // Act
        const auto& result = factory->getRepository(request);

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::data::repositories::FormDataRequestRepository>(result));
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

    SECTION("throws an NoAvailableRepositoryException when the request isn't an instance of FormDataRequestBody or RawRequestBody")
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