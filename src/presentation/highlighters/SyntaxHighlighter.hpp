#pragma once

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
            SyntaxHighlighter(QTextDocument* document);
            ~SyntaxHighlighter() override;

            void startHighlighting(std::list<SyntaxHighlighterRule*> rules);
            void stopHighlighting();

        protected:
            void highlightBlock(const QString& text) override;

        private:
            std::list<SyntaxHighlighterRule*> rules;
    };
}