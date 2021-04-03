#include "gui/highlighter/Highlighter.hpp"
#include "Highlighter.hpp"

using namespace getit::gui::highlighter;
using namespace getit::highlighter;

Highlighter::Highlighter(QTextDocument* document):
    QSyntaxHighlighter(document)
{

}

void Highlighter::startHighlighting(std::list<getit::highlighter::HighlighterRule*> rules)
{
    this->rules = rules;
    this->rehighlight();
}

void Highlighter::stopHighlighting()
{
    this->rules.clear();
    this->rehighlight();
}

void Highlighter::highlightBlock(const QString& text)
{
    for (HighlighterRule* rule : this->rules) {
        QRegularExpression pattern(QString::fromStdString(rule->regex));
        QTextCharFormat format;
        format.setForeground(QColor(rule->color));

        QRegularExpressionMatchIterator matchIterator = pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), format);
        }
    }
}