#pragma once

#include <string>

namespace getit::presentation::highlighters
{
    struct SyntaxHighlighterRule
    {
        public:
            std::string regex;
            int color;

            SyntaxHighlighterRule(std::string regex, int color):
                regex(regex), color(color) {}
    };
}