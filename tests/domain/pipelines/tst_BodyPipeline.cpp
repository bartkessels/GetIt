#include <catch2/catch.hpp>
#include <memory>

#include "domain/body/FormdataRequestBody.hpp"
#include "domain/body/RawRequestBody.hpp"
#include "domain/pipelines/BodyPipeline.hpp"
#include "domain/RequestData.hpp"

using namespace getit::domain;
using namespace getit::domain::pipelines;

// Check if body isn't set when the body is a nullptr
// Check if body 

TEST_CASE("BodyPipeline")
{
    SECTION("executeBeforeRequest sets the body given through the constructor on the RequestData pointer")
    {
        // Arrange
        const auto& requestData = std::make_shared<RequestData>();
        const auto& requestBody = std::make_shared<body::FormdataRequestBody>("boundary");
        requestBody->addElement("username", "checkmeout");
        requestBody->addElement("password", "orDont");

        const auto& sut = std::make_unique<BodyPipeline>(requestBody);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(requestData->getBody() == requestBody);
    }

    SECTION("when constructing a BodyPipeline with a nullptr for the RequestBody it throws an exception")
    {
        // Act & Assert
        REQUIRE_THROWS(std::make_unique<BodyPipeline>(nullptr));
    }
}