#pragma once

#include <memory>
#include <list>

#include "highlighter/HighlighterRule.hpp"

namespace getit::highlighter
{
    struct JsonHighlighterRules
    {
        public:
            inline static const auto& integerRule = new HighlighterRule(
                    "[+-]?([0-9]*[.])?[0-9]+",
                    0x0000ff
                );
            inline static const auto& stringRule = new HighlighterRule(
                    "\"(.*?)\"",
                    0x800080
                );
            
            inline static std::list<HighlighterRule*> rules = {
                    integerRule,
                    stringRule
            };
    };
}