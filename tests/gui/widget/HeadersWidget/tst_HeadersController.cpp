#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>

#include "domain/RequestData.hpp"
#include "gui/widget/HeadersWidget/HeadersController.hpp"

#include "./HeadersViewMock.hpp"

using namespace getit::gui::widget;

TEST_CASE("HeadersWidget/HeadersController")
{
    SECTION("Check if all headers from the view are added to the request data")
    {
        // Arrange
        nonUniqueMap expectedHeaders = {
            { "Content-Type", "application/json" },
            { "Accept-Language", "en-us" }
        };

        auto headersView = std::make_shared<HeadersViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*headersView.get(), getHeaders())
            .RETURN(expectedHeaders);

        const auto& sut = std::make_unique<HeadersController>(headersView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedHeaders == requestData->getHeaders());
    }
}