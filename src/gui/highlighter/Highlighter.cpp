#include "gui/highlighter/Highlighter.hpp"
#include "Highlighter.hpp"

using namespace getit::gui::highlighter;
using namespace getit::highlighter;

Highlighter::Highlighter(QTextDocument* document, std::list<HighlighterRule*> rules):
    QSyntaxHighlighter(document),
    rules(rules)
{

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
