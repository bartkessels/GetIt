#include <algorithm>
#include <catch2/catch.hpp>
#include <list>
#include <memory>
#include <string>
#include <utility>

#include "domain/pipelines/HeadersPipeline.hpp"

using namespace getit::domain;
using namespace getit::domain::pipelines;

TEST_CASE("HeadersPipeline")
{
    SECTION("executeBeforeRequest doesn't add any headers to the RequestData if no headers are set")
    {
        // Arrange
        const auto& requestData = std::make_shared<RequestData>();

        const auto& sut = std::make_unique<HeadersPipeline>();

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(requestData->getHeaders().empty());
    }

    SECTION("executeBeforeRequest adds the headers to the RequestData when they're set")
    {
        // Arrange
        auto header1 = "h1";
        auto header2 = "h2";

        std::list<std::pair<std::string, std::string>> expectedHeaders = {
            std::make_pair(header1, ""),
            std::make_pair(header2, "")
        };

        const auto& requestData = std::make_shared<RequestData>();

        const auto& sut = std::make_unique<HeadersPipeline>();

        // Act
        sut->addHeader(header1, "");
        sut->addHeader(header2, "");
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedHeaders == requestData->getHeaders());
    }
}