#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QMap>
#include "Headers/editor.h"


class QTextDocument;
/**
 * @brief The Highlighter class
 *
 * keyword
 * function
 * variable
 * funcion
 * control (for, while, if, switch)
 * comment
 * multilinecomment
 */
class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);
    Highlighter(Editor *parent);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QMap<QString, QVector<HighlightingRule>> highlightWithExtension;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;

public slots:
    void CRule();
    void CPPRule();
    void deleteRule();
    void PythonRule();
    void JavaRule();
    void MakeRule();
    void setupRule();
    void setupRule(QString extension);
   //void CppHighlightingRule();
   //void PythonHighlightingRule();
   //void JavaHighlightingRule();
   //void ArduinoHighlightingRule();

};

#endif // HIGHLIGHTER_H
