#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>
#include <filesystem>
#include <map>
#include <memory>
#include <string>

#include "domain/RequestData.hpp"
#include "gui/widget/BodyWidget/FormdataBodyTab/FormdataBodyTabController.hpp"

#include "./FormdataBodyTabView.hpp"

using namespace getit::gui::widget::BodyWidget;
using namespace getit::domain::body;

inline std::string getTestFile()
{
    std::string expectedLocation = "./bin/tst_file.txt";

    if (!std::filesystem::exists(expectedLocation)) {
        expectedLocation = "./tst_file.txt";
    }

    return expectedLocation;
}

TEST_CASE("BodyWidget/FormdataBodyTab/FormdataBodyTabController")
{
    SECTION("Check if all elements from the view are added to the body of the request data")
    {
        // Arrange
        auto element1Key = "username";
        auto element1Value = "someone";
        auto element2Key = "password";
        auto element2Value = "TopSecret!";

        std::map<std::string, std::string> expectedElements {
                {element1Key, element1Value},
                {element2Key, element2Value}
        };

        auto formdataView = std::make_shared<FormdataBodyTabViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*formdataView.get(), getElements())
            .RETURN(expectedElements);
        ALLOW_CALL(*formdataView.get(), getFiles())
            .RETURN((std::map<std::string, std::string>){});

        const auto& sut = std::make_unique<FormdataBodyTabController>(formdataView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(element1Key));
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(element1Value));
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(element2Key));
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(element2Value));
    }

    SECTION("Check if files from the view are added to the body of the request data")
    {
        // Arrange
        auto file1Key = "This is my test file";
        auto file1Path = getTestFile();
        auto expectedFileContent = "content";

        std::map<std::string, std::string> expectedFiles {
                {file1Key, file1Path}
        };

        auto formdataView = std::make_shared<FormdataBodyTabViewMock>();
        auto requestData = std::make_shared<getit::domain::RequestData>();

        ALLOW_CALL(*formdataView.get(), getElements())
            .RETURN((std::map<std::string, std::string>){});
        ALLOW_CALL(*formdataView.get(), getFiles())
            .RETURN(expectedFiles);

        const auto& sut = std::make_unique<FormdataBodyTabController>(formdataView);

        // Act
        sut->executeBeforeRequest(requestData);

        // Assert
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(file1Key));
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(file1Path));
        REQUIRE(std::string::npos != requestData->getBody()->getBody().find(expectedFileContent));
    }
}