#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>
#include <string>

#include "domain/RequestData.hpp"
#include "gui/widget/MethodWidget/MethodController.hpp"

#include "./MethodViewMock.hpp"

using namespace getit::gui::widget;

TEST_CASE("MethodWidget/MethodController")
{
    SECTION("Check if the method from the view is added to the request data")
    {
        // Arrange
        std::string expectedMethod = "PUT";

        auto methodView = std::make_shared<MethodViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*methodView.get(), getMethod())
            .RETURN(expectedMethod);

        const auto& sut = std::make_unique<MethodController>(methodView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedMethod == requestData->getMethod());
    }
}