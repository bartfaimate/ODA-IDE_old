#include "Headers/highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    setupRule();
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

void Highlighter::CRule()
{

}

void Highlighter::CPPRule()
{

    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\b__asm\\b" << "\\bauto\\b" << "\\bbool\\b"
                    << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
                    << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdelete\\b"
                    << "\\bdo\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
                    << "\\bexplicit\\b" << "\\bextern\\b" << "\\bfalse\\b"
                    << "\\bfriend\\b" << "\\bfloat\\b"  << "\\bfor\\b"
                    << "\\bgoto\\b"
                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\bnew\\b"
                    << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bsizeof\\b" << "\\bstatic\\b"
                    << "\\bstruct\\b" << "\\bswitch\\b"
                    << "\\btemplate\\b" << "\\bthis\\b" << "\\bthrow\\b"
                    <<"\\btypedef\\b" << "\\btypename\\b" << "\\btrue\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
                    << "\\breturn\\b"   ;
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::deleteRule()
{
    highlightingRules.clear();
}

void Highlighter::PythonRule()
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bFalse\\b" << "\\bNone\\b" << "\\bTrue\\b"
                    << "\\band\\b" << "\\bas\\b" << "\\bassert\\b"
                    << "\\bbreak\\b" << "\\bclass\\b" << "\\bcontinue\\b"
                    << "\\bdef\\b" << "\\bdel\\b" << "\\belif\\b"
                    << "\\belse\\b" << "\\bexcept\\b" << "\\bfinally\\b"
                    << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
                    << "\\bimport" << "\\bin\\b" << "\\bis\\b"
                    << "\\blambda\\b" << "\\bnonlocal\\b" << "\\bnot\\b"
                    << "\\bor\\b" << "\\bpass\\b" << "\\braise\\b"
                    << "\\breturn\\b" << "\\btry\\b" << "\\bwhile\\b"
                    << "\\bwith\\b" << "\\byield\\b" ;

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("'{3}|\"{3}");
    commentEndExpression = QRegularExpression("'{3}|\"{3}");

}

void Highlighter::JavaRule()
{

}

void Highlighter::MakeRule()
{

}

void Highlighter::setupRule()
{
    // CPPRule();
    PythonRule();

}

void Highlighter::setupRule(QString extension)
{
    deleteRule();
    QString lExtension = extension.toLower();
    if(lExtension == "py"){
        PythonRule();
    }
    else if (lExtension == "h" || extension == "hpp" || extension == "cpp" || extension == "c"){
        CPPRule();
    }
}
