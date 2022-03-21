#include "presentation/highlighters/SyntaxHighlighter.hpp"

using namespace getit::presentation::highlighters;

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* document):
        QSyntaxHighlighter(document)
{

}

void SyntaxHighlighter::startHighlighting(std::list<std::shared_ptr<SyntaxHighlighterRule>> rules)
{
    this->rules = rules;
    this->rehighlight();
}

void SyntaxHighlighter::stopHighlighting()
{
    this->rules.clear();
    this->rehighlight();
}

void SyntaxHighlighter::highlightBlock(const QString& text)
{
    for (const auto& rule : this->rules) {
        QRegularExpression pattern(QString::fromStdString(rule->regex));
        QTextCharFormat format;
        format.setForeground(QColor(rule->color));

        QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            const auto& match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), format);
        }
    }
}