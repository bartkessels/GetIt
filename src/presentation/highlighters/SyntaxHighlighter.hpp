#pragma once

#include <list>
#include <memory>
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QString>
#include <QTextCharFormat>
#include <QTextDocument>

#include "presentation/highlighters/SyntaxHighlighterRule.hpp"

namespace getit::presentation::highlighters
{
    class SyntaxHighlighter: public QSyntaxHighlighter
    {
        public:
            explicit SyntaxHighlighter(QTextDocument* document);
            ~SyntaxHighlighter() override = default;

            void startHighlighting(std::list<std::shared_ptr<SyntaxHighlighterRule>> rules);
            void stopHighlighting();

        protected:
            void highlightBlock(const QString& text) override;

        private:
            std::list<std::shared_ptr<SyntaxHighlighterRule>> rules;
    };
}