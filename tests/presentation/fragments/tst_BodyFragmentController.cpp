#include <catch2/catch.hpp>
#include <trompeloeil.hpp>
#include <memory>

#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"
#include "presentation/fragments/BodyFragment/IBodyFragmentView.hpp"

using namespace getit;
using namespace getit::domain::implementations;
using namespace getit::presentation::fragments;

class BodyFragmentViewMock: public IBodyFragmentView
{
    public:
        MAKE_MOCK0(getRawBody, std::shared_ptr<RawRequestBody>(), override);
        MAKE_MOCK0(getFormDataBody, std::shared_ptr<FormDataRequestBody>(), override);
        MAKE_MOCK0(getBodyType, BodyType(), override);
        MAKE_MOCK1(setFormDataBody, void(const std::shared_ptr<FormDataRequestBody>&), override);
        MAKE_MOCK1(setRawBody, void(const std::shared_ptr<RawRequestBody>&), override);
        MAKE_MOCK1(setBodyType, void(const BodyType&), override);
};

TEST_CASE("BodyFragmentController.getContent")
{
    // Before
    auto view = new BodyFragmentViewMock();
    const auto& sut = std::make_shared<BodyFragmentController>(view);

    SECTION("returns the formdata body from the view when the view returns FORM_DATA as the body type")
    {
        // Arrange
        const auto& body = std::make_shared<FormDataRequestBody>();
        const auto& bodyType = BodyType::FORM_DATA;

        ALLOW_CALL(*view, getBodyType()).RETURN(bodyType);
        ALLOW_CALL(*view, getFormDataBody()).RETURN(body);

        // Act
        const auto& actual = sut->getContent();

        // Assert
        REQUIRE(std::dynamic_pointer_cast<FormDataRequestBody>(actual));
    }

    SECTION("returns the raw body from the view when the view returns RAW as the body type")
    {
        // Arrange
        const auto& body = std::make_shared<RawRequestBody>();
        const auto& bodyType = BodyType::RAW;

        ALLOW_CALL(*view, getBodyType()).RETURN(bodyType);
        ALLOW_CALL(*view, getRawBody()).RETURN(body);

        // Act
        const auto& actual = sut->getContent();

        // Assert
        REQUIRE(std::dynamic_pointer_cast<RawRequestBody>(actual));
    }
}

TEST_CASE("BodyFragmentController.setContent")
{
    // Before
    auto view = new BodyFragmentViewMock();
    const auto& sut = std::make_shared<BodyFragmentController>(view);

    SECTION("calls setBody with the formData body when the implementation is FormDataRequestBody")
    {
        // Arrange
        const auto& body = std::make_shared<FormDataRequestBody>();

        // Assert
        REQUIRE_CALL(*view, setFormDataBody(body));

        // Act
        sut->setContent(body);
    }

    SECTION("calls setBody with the raw body when the implementation is RawRequestBody")
    {
        // Arrange
        const auto& body = std::make_shared<RawRequestBody>();

        // Assert
        REQUIRE_CALL(*view, setRawBody(body));

        // Act
        sut->setContent(body);
    }
}