#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <map>
#include <memory>
#include <string>

#include "presentation/fragments/HeadersFragment/HeadersFragmentController.hpp"
#include "presentation/fragments/HeadersFragment/IHeadersFragmentView.hpp"

using namespace getit;
using namespace getit::presentation::fragments;
using trompeloeil::_;

class HeadersFragmentViewMock: public IHeadersFragmentView
{
    public:
        MAKE_MOCK0(getHeaders, (std::map<std::string, std::string>()), override);
        MAKE_MOCK1(setHeaders, void(const std::map<std::string, std::string>&), override);
};

TEST_CASE("HeadersFragmentController.getContent")
{
    // Before
    auto view = new HeadersFragmentViewMock();
    const auto& sut = std::make_shared<HeadersFragmentController>(view);

    SECTION("returns the headers from the view")
    {
        // Arrange
        std::map<std::string, std::string> expectedHeaders = {
                { "Content-Type", "application/json" },
                { "Set-Cookies", "we-track-you=always" }
        };

        ALLOW_CALL(*view, getHeaders()).RETURN(expectedHeaders);

        // Act
        const auto& actual = sut->getContent();

        // Assert
        REQUIRE(actual == expectedHeaders);
    }
}


TEST_CASE("HeadersFragmentController.setContent")
{
    // Before
    auto view = new HeadersFragmentViewMock();
    const auto& sut = std::make_shared<HeadersFragmentController>(view);

    SECTION("calls setHeaders on the view")
    {
        // Arrange
        std::map<std::string, std::string> expectedHeaders = {
                { "Content-Type", "application/json" },
                { "Set-Cookies", "we-track-you=always" }
        };

        // Assert
        REQUIRE_CALL(*view, setHeaders(expectedHeaders));

        // Act
        sut->setContent(expectedHeaders);
    }
}