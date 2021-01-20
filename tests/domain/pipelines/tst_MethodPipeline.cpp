#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/pipelines/MethodPipeline.hpp"
#include "domain/RequestData.hpp"

using namespace getit::domain;
using namespace getit::domain::pipelines;

TEST_CASE("MethodPipeline")
{
    SECTION("executeBeforeRequest sets the method given through the constructor on the RequestData pointer")
    {
        // Arrange
        std::string method = "GET";
        const auto& requestData = std::make_shared<RequestData>();

        const auto& sut = std::make_unique<MethodPipeline>(method);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(requestData->getMethod() == method);
    }
}