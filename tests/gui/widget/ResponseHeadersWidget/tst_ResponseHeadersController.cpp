#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <map>
#include <memory>

#include "domain/Response.hpp"
#include "gui/widget/ResponseHeadersWidget/ResponseHeadersController.hpp"

#include "./ResponseHeadersViewMock.hpp"

using namespace getit::gui::widget;

TEST_CASE("ResponseHeadersWidget/ResponseHeadersController")
{
    SECTION("Check if the headers from the response are passed as-is to the view")
    {
        // Arrange
        auto expectedHeaders = std::map<std::string, std::string> {
            { "Accept-Language", "en-US" },
            { "Content-Type", "application/json" }
        };

        auto response = std::make_shared<getit::domain::Response>();
        auto responseHeadersView = std::make_shared<ResponseHeadersViewMock>();
        const auto& sut = std::make_unique<ResponseHeadersController>(responseHeadersView);

        // Act
        response->headers = expectedHeaders;
        sut->executeAfterRequest(response);

        // Assert
        REQUIRE_CALL(*responseHeadersView.get(), setHeaders(response->headers));
    }
}