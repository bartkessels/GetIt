#pragma once

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
    };
}