#include <catch2/catch.hpp>
#include <memory>
#include <string>

#include "domain/models/Variable.hpp"

using namespace getit::domain::models;

TEST_CASE("Variable.apply")
{
    SECTION("replaces nothing when the casing of the variable name doesn't match")
    {
        // Arrange
        const auto& variableName = "Test-Variable";
        const auto& variableValue = "This is my test content";
        const auto& input = "{test-variable}";

        const auto& variable = std::make_unique<Variable>(variableName, variableValue);

        // Act
        const auto& result = variable->apply(input);

        // Assert
        REQUIRE(result != variableValue);
        REQUIRE(result == input);
    }

    SECTION("replaces nothing when the variable is not in the input string")
    {
        // Arrange
        const auto& variableName = "Test-Variable";
        const auto& variableValue = "This is my test content";
        const auto& input = "{unknown-variable}";

        const auto& variable = std::make_unique<Variable>(variableName, variableValue);

        // Act
        const auto& result = variable->apply(input);

        // Assert
        REQUIRE(result != variableValue);
        REQUIRE(result == input);
    }

    SECTION("replaces variable name with value")
    {
        // Arrange
        const auto& variableName = "test-variable";
        const auto& variableValue = "This is my test content";
        const auto& input = "{test-variable}";

        const auto& variable = std::make_unique<Variable>(variableName, variableValue);

        // Act
        const auto& result = variable->apply(input);

        // Assert
        REQUIRE(result == variableValue);
        REQUIRE(result != input);
    }

    SECTION("replace only known variable name with value")
    {
        // Arrange
        const auto& variableName = "test-variable";
        const auto& variableValue = "This is my test content";
        const auto& input = "{test-variable} - {unknown-variable}";
        const auto& expected = "This is my test content - {unknown-variable}";

        const auto& variable = std::make_unique<Variable>(variableName, variableValue);

        // Act
        const auto& result = variable->apply(input);

        // Assert
        REQUIRE(result == expected);
        REQUIRE(result != input);
    }

    SECTION("replaces all occurrences of the variable")
    {
        // Arrange
        const auto& variableName = "test-variable";
        const auto& variableValue = "This is my test content";
        const auto& input = "{test-variable} - {test-variable}";
        const auto& expected = "This is my test content - This is my test content";

        const auto& variable = std::make_unique<Variable>(variableName, variableValue);

        // Act
        const auto& result = variable->apply(input);

        // Assert
        REQUIRE(result == expected);
        REQUIRE(result != input);
    }

    SECTION("returns empty string when the input is empty")
    {
        // Arrange
        const auto& variable = std::make_unique<Variable>("key", "value");

        // Act
        const auto& result = variable->apply("");

        // Assert
        REQUIRE(result.empty());
    }
}
