#pragma once

#include <list>
#include <memory>

#include "presentation/highlighters/SyntaxHighlighterRule.hpp"

namespace getit::presentation::highlighters
{
    struct XmlSyntaxHighlighterRule
    {
        public:
            inline static const auto& tagRule = std::make_shared<SyntaxHighlighterRule>(
                    "<[^>]*>|<[^>]*/[^>]*\\?>",
                    0x72bcd4
            );
            inline static const auto& attributeValueRule = std::make_shared<SyntaxHighlighterRule>(
                    "\"(.*?)\"",
                    0x800080
            );
            inline static const auto& commentRule = std::make_shared<SyntaxHighlighterRule>(
                    "<!--[\\s\\S]*?-->",
                    0x00ff00
            );
            inline static const auto& entityRule = std::make_shared<SyntaxHighlighterRule>(
                    "&[^-\\s][\\s\\S]*?[^-\\s];",
                    0x0000ff
            );

            inline static std::list<std::shared_ptr<SyntaxHighlighterRule>> rules = {
                    tagRule,
                    entityRule,
                    attributeValueRule,
                    commentRule
            };
    };
}