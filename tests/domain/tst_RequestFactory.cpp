#include <catch2/catch.hpp>
#include <memory>

#include "domain/request/CppRestRequest.hpp"
#include "domain/Request.hpp"
#include "domain/RequestFactory.hpp"

using namespace getit::domain;

TEST_CASE("RequestFactory")
{
    SECTION("getRequest returns an instance of CppRestRequest")
    {
        // Arrange
        const auto& sut = std::make_shared<RequestFactory>();

        // Act
        std::shared_ptr<Request> result = sut->getRequest();

        // Assert
        REQUIRE(dynamic_cast<request::CppRestRequest*>(result.get()));
    }
}