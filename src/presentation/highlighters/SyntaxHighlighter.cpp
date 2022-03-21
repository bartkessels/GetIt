#include "presentation/highlighters/SyntaxHighlighter.hpp"

using namespace getit::presentation::highlighters;

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* document):
        QSyntaxHighlighter(document)
{

}

SyntaxHighlighter::~SyntaxHighlighter()
{
    while(!rules.empty()) {
        delete rules.back();
    }
}

void SyntaxHighlighter::startHighlighting(std::list<SyntaxHighlighterRule*> rules)
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
    for (SyntaxHighlighterRule* rule : this->rules) {
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