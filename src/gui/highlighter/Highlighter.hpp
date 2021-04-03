#pragma once

#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QString>
#include <QTextCharFormat>
#include <QTextDocument>

#include "highlighter/HighlighterRule.hpp"

namespace getit::gui::highlighter
{
    class Highlighter: public QSyntaxHighlighter
    {
        Q_OBJECT

        public:
            Highlighter(QTextDocument* document);
            ~Highlighter() = default;

            void startHighlighting(std::list<getit::highlighter::HighlighterRule*> rules);
            void stopHighlighting();

        protected:
            void highlightBlock(const QString& text) override;

        private:
            std::list<getit::highlighter::HighlighterRule*> rules;
    };
}
