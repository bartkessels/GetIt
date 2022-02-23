#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <memory>

#include "data/exceptions/NoAvailableRepositoryException.hpp"
#include "data/factories/RequestRepositoryFactory.hpp"
#include "data/repositories/RequestRepository.hpp"
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

    SECTION("returns an instance of RequestRepository")
    {
        // Arrange
        // Act
        const auto& result = factory->getRepository();

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::data::repositories::RequestRepository>(result));
    }
}