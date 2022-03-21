#pragma once

#include <list>
#include <memory>

#include "presentation/highlighters/SyntaxHighlighterRule.hpp"

namespace getit::presentation::highlighters
{
    struct JsonSyntaxHighlighterRule
    {
        public:
            inline static const auto& integerRule = std::make_shared<SyntaxHighlighterRule>(
                    "[+-]?([0-9]*[.])?[0-9]+",
                    0x0000ff
            );
            inline static const auto& stringRule = std::make_shared<SyntaxHighlighterRule>(
                    "\"(.*?)\"",
                    0x800080
            );

            inline static std::list<std::shared_ptr<SyntaxHighlighterRule>> rules = {
                    integerRule,
                    stringRule
            };
    };
}