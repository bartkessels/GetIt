#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <memory>
#include <string>

#include "domain/RequestData.hpp"
#include "gui/widget/CookiesWidget/CookiesController.hpp"

#include "./CookiesViewMock.hpp"

using namespace getit::gui::widget;

TEST_CASE("CookiesWidget/CookiesController")
{
    SECTION("Check if all cookies from the view are added to the request data")
    {
        // Arrange
        nonUniqueMap expectedCookies = {
            { "UserId", "1" },
            { "IsAuthenticated", "true" }
        };

        auto cookiesView = std::make_shared<CookiesViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*cookiesView.get(), getCookies())
            .RETURN(expectedCookies);

        const auto& sut = std::make_unique<CookiesController>(cookiesView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedCookies.size() == requestData->getHeaders().size());
    }

    SECTION("Check if the cookie header value is in the 'COOKIE'='VALUE' format")
    {
        // Arrange
        std::string cookie1 = "UserId";
        std::string cookie1Value = "1";

        std::string expectedCookie = cookie1 + "=" + cookie1Value;

        nonUniqueMap expectedCookies = {
            { cookie1, cookie1Value }
        };

        auto cookiesView = std::make_shared<CookiesViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*cookiesView.get(), getCookies()).RETURN(expectedCookies);

        const auto& sut = std::make_unique<CookiesController>(cookiesView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedCookie == requestData->getHeaders().front().second);
    }

    SECTION("Check if one cookie per Set-Cookie is set in the headers")
    {
        // Arrange
        std::string cookie1 = "UserId";
        std::string cookie1Value = "1";
        std::string cookie2 = "IsAuthenticated";
        std::string cookie2Value = "false";

        nonUniqueMap expectedCookies = {
            { cookie1, cookie1Value },
            { cookie2, cookie2Value }
        };

        nonUniqueMap expectedHeaders = {
            { "Set-Cookie", cookie1 + "=" + cookie1Value },
            { "Set-Cookie", cookie2 + "=" + cookie2Value }
        };

        auto cookiesView = std::make_shared<CookiesViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*cookiesView.get(), getCookies()).RETURN(expectedCookies);

        const auto& sut = std::make_unique<CookiesController>(cookiesView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(expectedHeaders == requestData->getHeaders());
    }
}
