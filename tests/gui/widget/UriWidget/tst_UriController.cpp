#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>
#include <string>

#include "domain/RequestData.hpp"
#include "gui/widget/UriWidget/UriController.hpp"

#include "./UriViewMock.hpp"

using namespace getit::gui::widget;

TEST_CASE("UriWidget/UriController")
{
    SECTION("Check if the uri from the view is added to the request data")
    {
        // Arrange
        std::string expectedUri = "https://github.com/bartkessels/getit";

        auto uriView = std::make_shared<UriViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*uriView.get(), getUri())
            .RETURN(expectedUri);

        const auto& sut = std::make_unique<UriController>(uriView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Arrange
        REQUIRE(expectedUri == requestData->getUri());
    }
}