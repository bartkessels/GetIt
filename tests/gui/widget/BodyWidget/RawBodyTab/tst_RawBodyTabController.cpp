#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>
#include <string>

#include "domain/RequestData.hpp"
#include "gui/widget/BodyWidget/RawBodyTab/RawBodyTabController.hpp"

#include "./RawBodyTabViewMock.hpp"

using namespace getit::gui::widget::BodyWidget;

TEST_CASE("BodyWidget/RawBodyTab/RawBodyTabController")
{
    SECTION("Check if the body from the view is added to the request data")
    {
        // Arrange
        std::string expectedBody = R"({ "custom": "body"; })";

        auto tabView = std::make_shared<RawBodyTabViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*tabView.get(), getBody())
            .RETURN(expectedBody);
        ALLOW_CALL(*tabView.get(), getContentType())
            .RETURN("");

        const auto& sut = std::make_unique<RawBodyTabController>(tabView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedBody == requestData->getBody()->getBody());
    }

    SECTION("Check if the content type from the view is added to the request data")
    {
        // Arrange
        std::string expectedContentType = "application/json";

        auto tabView = std::make_shared<RawBodyTabViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*tabView.get(), getBody())
            .RETURN("");
        ALLOW_CALL(*tabView.get(), getContentType())
            .RETURN(expectedContentType);

        const auto& sut = std::make_unique<RawBodyTabController>(tabView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedContentType == requestData->getBody()->getContentType());
    }
}