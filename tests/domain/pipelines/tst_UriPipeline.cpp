#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/pipelines/UriPipeline.hpp"
#include "domain/RequestData.hpp"

using namespace getit::domain;
using namespace getit::domain::pipelines;

TEST_CASE("UriPipeline")
{
    SECTION("executeBeforeRequest sets the method given through the constructor on the RequestData pointer")
    {
        // Arrange
        std::string uri = "https://bartkessels.net";
        const auto& requestData = std::make_shared<RequestData>();

        const auto& sut = std::make_unique<UriPipeline>(uri);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(requestData->getUri() == uri);
    }
}