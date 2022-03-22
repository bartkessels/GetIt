#pragma once

#include <string>
#include <utility>

namespace getit::presentation::highlighters
{
    struct SyntaxHighlighterRule
    {
        public:
            std::string regex;
            int color;

            SyntaxHighlighterRule(std::string regex, int color):
                regex(std::move(regex)), color(color) {}
    };
}