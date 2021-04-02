#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>
#include <string>

#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/RawResponseBodyTabController.hpp"

#include "./RawResponseBodyTabViewMock.hpp"

using namespace getit::gui::widget::ResponseBodyWidget;

TEST_CASE("ResponseBodyWidget/RawResponseBodyTabController")
{
    SECTION("Check if the body from the response is added to the view")
    {
        // Arrange
        std::string expectedBody = "This is my raw body";

        auto tabView = std::make_shared<RawResponseBodyTabViewMock>();
        auto response = std::make_shared<getit::domain::Response>();
        response->body = expectedBody;

        const auto& sut = std::make_unique<RawResponseBodyTabController>(tabView);

        // Assert (assert before making the call, otherwise the call won't be registered!)
        REQUIRE_CALL(*tabView.get(), setBody(expectedBody));

        // Act
        sut->executeAfterRequest(response);
    }
}