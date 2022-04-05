#include <catch2/catch.hpp>
#include <regex>

#include "presentation/highlighters/XmlSyntaxHighlighterRule.hpp"

using namespace getit::presentation::highlighters;

TEST_CASE("XmlSyntaxHighlighterRule - tagRule")
{
    SECTION("Allows empty tags")
    {
        // Arrange
        const auto& inputValue = "<tag />";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows tags with attributes")
    {
        // Arrange
        const auto& inputValue = R"(<user name="Bart" />)";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows starting tags with attributes")
    {
        // Arrange
        const auto& inputValue = R"(<user name="Bart">)";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows starting tags without attributes")
    {
        // Arrange
        const auto& inputValue = "<user>";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows ending tags without attributes")
    {
        // Arrange
        const auto& inputValue = "</user>";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows XML starting tags (<?xml ?>)")
    {
        // Arrange
        const auto& inputValue = "<?xml ?>";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows XML starting tags with attributes (<?xml ?>)")
    {
        // Arrange
        const auto& inputValue = R"(<?xml version="1.0" ?>)";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows XML starting tags with attributes (<?xml ?>)")
    {
        // Arrange
        const auto& inputValue = "<!DOCTYPE html>";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows comments (<!-- ... -->)")
    {
        // Arrange
        const auto& inputValue = "<!-- -->";
        std::regex regex(XmlSyntaxHighlighterRule::tagRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }
}

TEST_CASE("XmlSyntaxHighlighterRule - attributeValueRule")
{
    SECTION("Does not allow values without quotes")
    {
        // Arrange
        const auto& inputValue = "This is my value";
        std::regex regex(XmlSyntaxHighlighterRule::attributeValueRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Allows values within double quotes")
    {
        // Arrange
        const auto& inputValue = R"("This is my value")";
        std::regex regex(XmlSyntaxHighlighterRule::attributeValueRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Does not allow values within single quotes")
    {
        // Arrange
        const auto& inputValue = "'This is my value'";
        std::regex regex(XmlSyntaxHighlighterRule::attributeValueRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }
}

TEST_CASE("XmlSyntaxHighlighterRule - commentRule")
{
    SECTION("Allows string that start with <!-- and end with -->")
    {
        // Arrange
        const auto& inputValue = "<!-- This is my comment -->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows string that's directly attached to the starting point (<!--)")
    {
        // Arrange
        const auto& inputValue = "<!--This is my comment -->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows string that's directly attached to the ending point (-->)")
    {
        // Arrange
        const auto& inputValue = "<!-- This is my comment-->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows string that's directly attached to both the starting and ending point")
    {
        // Arrange
        const auto& inputValue = "<!--This is my comment-->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows string that only exists of the starting and ending points with a space in between")
    {
        // Arrange
        const auto& inputValue = "<!-- -->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows string that only exists of the starting and ending points directly attached to each other")
    {
        // Arrange
        const auto& inputValue = "<!---->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Does not allow string that only start with <!-- and does NOT end with -->")
    {
        // Arrange
        const auto& inputValue = "<!-- This is my comment";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string that does NOT start with <!-- but ends with -->")
    {
        // Arrange
        const auto& inputValue = "This is my comment -->";
        std::regex regex(XmlSyntaxHighlighterRule::commentRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }
}

TEST_CASE("XmlSyntaxHighlighterRule - entityRule")
{
    SECTION("Allows values that start with an ampersand (&) and end with a semicolon (;)")
    {
        // Arrange
        const auto& inputValue = "&amp;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Does not allow values that only start with an ampersand (&) but do NOT end with a semicolon (;)")
    {
        // Arrange
        const auto& inputValue = "&amp";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow values that do NOT start with an ampersand (&) but do end with a semicolon (;)")
    {
        // Arrange
        const auto& inputValue = "amp;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string that's not directly attached to the starting point (&)")
    {
        // Arrange
        const auto& inputValue = "& amp;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string that's not directly attached to the ending point (;)")
    {
        // Arrange
        const auto& inputValue = "&amp ;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string that's not directly attached to either the starting or ending point")
    {
        // Arrange
        const auto& inputValue = "& amp ;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string that only exists of the starting and ending points with a space in between")
    {
        // Arrange
        const auto& inputValue = "& ;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string that only exists of the starting and ending points directly attached to each other")
    {
        // Arrange
        const auto& inputValue = "&;";
        std::regex regex(XmlSyntaxHighlighterRule::entityRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }
}