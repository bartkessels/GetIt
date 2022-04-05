#include <catch2/catch.hpp>
#include <regex>

#include "presentation/highlighters/JsonSyntaxHighlighterRule.hpp"

using namespace getit::presentation::highlighters;

TEST_CASE("JsonHighlighterRules - integerRule")
{
    SECTION("Allows - (minus) sign in front of number")
    {
        // Arrange
        const auto& inputValue = "-2";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Does not allow - (minus) sign after number")
    {
        // Arrange
        const auto& inputValue = "2-";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Allows + (plus) sign in front of number")
    {
        // Arrange
        const auto& inputValue = "+2";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Does not allow + (plus) sign after number")
    {
        // Arrange
        const auto& inputValue = "2+";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow number in double quotes")
    {
        // Arrange
        const auto& inputValue = "\"2\"";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow number in single quotes")
    {
        // Arrange
        const auto& inputValue = "'2'";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Allows floating point numbers with . (dot)")
    {
        // Arrange
        const auto& inputValue = "2.21";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows floating point numbers with large amount of numbers before the . (dot)")
    {
        // Arrange
        const auto& inputValue = "232248796434843.21";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Allows floating point numbers with large amount of numbers after the . (dot)")
    {
        // Arrange
        const auto& inputValue = "2.21232248796434843";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }

    SECTION("Does not allow floating point numbers with , (comma)")
    {
        // Arrange
        const auto& inputValue = "2,21";
        std::regex regex(JsonSyntaxHighlighterRule::integerRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }
}

TEST_CASE("JsonHighlighterRules - stringRule")
{
    SECTION("Allows string within double quotes")
    {
        // Arrange
        const auto& inputValue = R"("This is my string")";
        std::regex regex(JsonSyntaxHighlighterRule::stringRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
    REQUIRE(result == true);
    }

    SECTION("Does not allow string within single quotes")
    {
        // Arrange
        const auto& inputValue = "'This is my string'";
        std::regex regex(JsonSyntaxHighlighterRule::stringRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Does not allow string without quotes")
    {
        // Arrange
        const auto& inputValue = "This is my string";
        std::regex regex(JsonSyntaxHighlighterRule::stringRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == false);
    }

    SECTION("Allows numbers")
    {
        // Arrange
        const auto& inputValue = R"("This is my string with the number 5")";
        std::regex regex(JsonSyntaxHighlighterRule::stringRule->regex);

        // Act
        std::cmatch match;
        const bool result = std::regex_match(inputValue, match, regex);

        // Assert
        REQUIRE(result == true);
    }
}