#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <map>
#include <memory>
#include <string>

#include "presentation/fragments/ResponseFragment/ResponseFragmentController.hpp"
#include "presentation/fragments/ResponseFragment/IResponseFragmentView.hpp"

using namespace getit;
using namespace getit::presentation::fragments;

class ResponseFragmentViewMock: public IResponseFragmentView
{
    public:
        MAKE_MOCK0(getHeaders, (std::map<std::string, std::string>()), override);
        MAKE_MOCK0(getBody, std::string(), override);
        MAKE_MOCK1(setHeaders, void(const std::map<std::string, std::string>&), override);
        MAKE_MOCK1(setBody, void(const std::string&), override);
        MAKE_MOCK0(clearHeaders, void(), override);
};

TEST_CASE("ResponseFragmentController.getContent")
{
    // Before
    auto view = new ResponseFragmentViewMock();
    const auto &sut = std::make_shared<ResponseFragmentController>(view);

    SECTION("returns the headers from the view")
    {
        // Arrange
        std::map<std::string, std::string> expectedHeaders = {
                { "Content-Type", "application/json" },
                { "Set-Cookies", "we-track-you=always" }
        };

        ALLOW_CALL(*view, getHeaders()).RETURN(expectedHeaders);
        ALLOW_CALL(*view, getBody()).RETURN("");

        // Act
        const auto& actual = sut->getContent();

        // Assert
        REQUIRE(actual->headers == expectedHeaders);
    }

    SECTION("returns the body from the view")
    {
        // Arrange
        const auto& expectedBody = "This is my response body";

        ALLOW_CALL(*view, getHeaders()).RETURN(std::map<std::string, std::string>());
        ALLOW_CALL(*view, getBody()).RETURN(expectedBody);

        // Act
        const auto& actual = sut->getContent();

        // Assert
        REQUIRE(actual->body == expectedBody);
    }
}


TEST_CASE("ResponseFragmentController.setContent")
{
    // Before
    auto view = new ResponseFragmentViewMock();
    const auto &sut = std::make_shared<ResponseFragmentController>(view);

    SECTION("calls clearHeaders on the view")
    {
        // Arrange
        ALLOW_CALL(*view, clearHeaders());
        ALLOW_CALL(*view, setHeaders(trompeloeil::_));
        ALLOW_CALL(*view, setBody(trompeloeil::_));

        const auto& response = std::make_shared<domain::models::Response>();

        // Assert
        REQUIRE_CALL(*view, clearHeaders());

        // Act
        sut->setContent(response);
    }

    SECTION("calls setHeaders on the view")
    {
        // Arrange
        ALLOW_CALL(*view, clearHeaders());
        ALLOW_CALL(*view, setBody(trompeloeil::_));

        std::map<std::string, std::string> expectedHeaders = {
                { "Content-Type", "application/json" },
                { "Set-Cookies", "we-track-you=always" }
        };

        const auto& response = std::make_shared<domain::models::Response>();
        response->headers = expectedHeaders;

        // Assert
        REQUIRE_CALL(*view, setHeaders(expectedHeaders));

        // Act
        sut->setContent(response);
    }

    SECTION("calls clearHeaders before setHeaders on the view")
    {
        // Arrange
        trompeloeil::sequence seq;
        ALLOW_CALL(*view, setBody(trompeloeil::_));

        std::map<std::string, std::string> expectedHeaders = {
                { "Content-Type", "application/json" },
                { "Set-Cookies", "we-track-you=always" }
        };

        const auto& response = std::make_shared<domain::models::Response>();
        response->headers = expectedHeaders;

        // Assert
        REQUIRE_CALL(*view, clearHeaders()).IN_SEQUENCE(seq);
        REQUIRE_CALL(*view, setHeaders(expectedHeaders)).IN_SEQUENCE(seq);

        // Act
        sut->setContent(response);
    }

    SECTION("calls setBody on the view")
    {
        // Arrange
        ALLOW_CALL(*view, clearHeaders());
        ALLOW_CALL(*view, setHeaders(trompeloeil::_));
        ALLOW_CALL(*view, setBody(trompeloeil::_));

        const auto& expectedBody = "This is my response body";

        const auto& response = std::make_shared<domain::models::Response>();
        response->body = expectedBody;

        // Assert
        REQUIRE_CALL(*view, setBody(expectedBody));

        // Act
        sut->setContent(response);
    }
}
