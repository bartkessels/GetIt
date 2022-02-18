#include <catch2/catch.hpp>
#include <memory>

#include "service/factories/RequestServiceFactory.hpp"
#include "service/implementations/CppRestRequestService.hpp"

using namespace getit::service::factories;

TEST_CASE("RequestServiceFactory.getRequestService")
{
    const auto& factory = std::make_shared<RequestServiceFactory>();

    SECTION("Returns an instance of CppRestRequestService")
    {
        // Act
        const auto& result = factory->getRequestService();

        // Assert
        REQUIRE(std::dynamic_pointer_cast<getit::service::implementations::CppRestRequestService>(result));
    }
}