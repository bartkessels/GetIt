#pragma once

#include <list>

#include "highlighter/HighlighterRule.hpp"

namespace getit::highlighter
{
    struct XmlHighlighterRules
    {
        public:
            inline static const auto& tagRule = new HighlighterRule(
                    "<[^>]*>|<[^>]*/[^>]*\\?>",
                    0x72bcd4
                );
            inline static const auto& attributeValueRule = new HighlighterRule(
                    "\"(.*?)\"",
                    0x800080
                );
            inline static const auto& commentRule = new HighlighterRule(
                    "<!--[\\s\\S]*?-->",
                    0x00ff00
                );
            inline static const auto& entityRule = new HighlighterRule(
                    "&[^-\\s][\\s\\S]*?[^-\\s];",
                    0x0000ff
                );

            inline static std::list<HighlighterRule*> rules = {
                    tagRule,
                    entityRule,
                    attributeValueRule,
                    commentRule
            };
    };
}
