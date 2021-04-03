#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>
#include <string>

#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/XmlResponseBodyTabController.hpp"

#include "./XmlResponseBodyTabViewMock.hpp"

using namespace getit::gui::widget::ResponseBodyWidget;

TEST_CASE("ResponseBodyWidget/XmlResponseBodyTabController")
{
    SECTION("Check if the body from the request is added to the view")
    {
        // Arrange
        std::string expectedBody = "<user id=\"41235\"><name>Bart</name><age>25</age></user>";

        auto tabView = std::make_shared<XmlResponseBodyTabViewMock>();
        auto response = std::make_shared<getit::domain::Response>();
        response->body = expectedBody;

        const auto& sut = std::make_unique<XmlResponseBodyTabController>(tabView);

        // Assert (assert before making the call, otherwise the call won't be registered!)
        REQUIRE_CALL(*tabView.get(), setBody(expectedBody));

        // Act
        sut->executeAfterRequest(response);
    }
}