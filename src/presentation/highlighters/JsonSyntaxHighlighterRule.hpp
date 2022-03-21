#pragma once

#include <list>

#include "presentation/highlighters/SyntaxHighlighterRule.hpp"

namespace getit::presentation::highlighters
{
    struct JsonSyntaxHighlighterRule
    {
        public:
            inline static const auto& integerRule = new SyntaxHighlighterRule(
                    "[+-]?([0-9]*[.])?[0-9]+",
                    0x0000ff
            );
            inline static const auto& stringRule = new SyntaxHighlighterRule(
                    "\"(.*?)\"",
                    0x800080
            );

            inline static std::list<SyntaxHighlighterRule*> rules = {
                    integerRule,
                    stringRule
            };
    };
}