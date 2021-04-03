#pragma once

#include <regex>
#include <string>

namespace getit::highlighter
{
    struct HighlighterRule
    {
        public:
            std::string regex;
            int color;

            HighlighterRule(std::string regex, int color):
                regex(regex), color(color) {}

            bool matches(std::string value) {
                return std::regex_match(
                        value,
                        std::regex(regex)
                    );
            }
    };
}