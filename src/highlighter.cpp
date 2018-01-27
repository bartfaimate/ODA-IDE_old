#include "Headers/highlighter.h"
#include <QBrush>
#include <QColor>

/**
 * @brief Highlighter::Highlighter
 * @param parent
 */
Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    setupRule();
}
/**
 * @brief Highlighter::highlightBlock
 * @param text
 */
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

/**
 * @brief Highlighter::CRule
 */
//void Highlighter::CRule()
//{
//    HighlightingRule rule;
//    keywordFormat.setForeground(Qt::darkBlue);
//    keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\b__asm\\b" << "\\bbreak\\b" << "\\bcase\\b"
//                    << "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
//                    << "\\bdefault\\b" << "\\bdo\\b"
//                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
//                    << "\\bextern\\b" << "\\bfloat\\b"  << "\\bfor\\b"
//                    << "\\bgoto\\b"
//                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
//                    << "\\blong\\b" << "\\bshort\\b" << "\\bsigned\\b"
//                    << "\\bsizeof\\b" << "\\bstatic\\b"
//                    << "\\bstruct\\b" << "\\bswitch\\b"
//                    <<"\\btypedef\\b" << "\\btypename\\b"
//                    << "\\bunion\\b" << "\\bunsigned\\b"
//                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
//                    << "\\breturn\\b"   ;
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = keywordFormat;
//        highlightingRules.append(rule);
//    }

//    keywordPatterns.clear();
//    macroFormat.setFontWeight(QFont::Bold);
//    macroFormat.setForeground(Qt::magenta);
//    keywordPatterns << "#\\binclude\\b" << "#\\bif\\b" << "#\\bifndef\\b"
//                  << "#\\belse\\b" << "#\\bendif\\b" << "#\\bdefine\\b"
//                  << "#\\bundef\\b" << "#\\bdefine\\b" << "#\\bpragma\\b"
//                  ;
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = macroFormat;
//        highlightingRules.append(rule);
//    }

//    singleLineCommentFormat.setForeground(Qt::red);
//    rule.pattern = QRegularExpression("//[^\n]*");
//    rule.format = singleLineCommentFormat;
//    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::red);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegularExpression("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegularExpression("/\\*");
//    commentEndExpression = QRegularExpression("\\*/");
//}

/**
 * @brief Highlighter::CRule
 * @param keywordColor
 * @param macroColor
 * @param commentColor
 * @param stringColor
 * @param functionColor
 */
void Highlighter::CRule(QString keywordColor = "darkblue", QString macroColor = "magenta", QString commentColor = "darkgreen", QString stringColor = "green", QString functionColor = "blue")
{
    QColor color(keywordColor);
    QBrush brush(color);
    HighlightingRule rule;
    keywordFormat.setForeground(brush);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\b__asm\\b" << "\\bbreak\\b" << "\\bcase\\b"
                    << "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
                    << "\\bdefault\\b" << "\\bdo\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
                    << "\\bextern\\b" << "\\bfloat\\b"  << "\\bfor\\b"
                    << "\\bgoto\\b"
                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
                    << "\\blong\\b" << "\\bshort\\b" << "\\bsigned\\b"
                    << "\\bsizeof\\b" << "\\bstatic\\b"
                    << "\\bstruct\\b" << "\\bswitch\\b"
                    <<"\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
                    << "\\breturn\\b"   ;
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    keywordPatterns.clear();
    color.setNamedColor(macroColor);
    brush.setColor(color);
    macroFormat.setFontWeight(QFont::Bold);
    macroFormat.setForeground(brush);
    keywordPatterns << "#\\binclude\\b" << "#\\bif\\b" << "#\\bifndef\\b"
                  << "#\\belse\\b" << "#\\bendif\\b" << "#\\bdefine\\b"
                  << "#\\bundef\\b" << "#\\bdefine\\b" << "#\\bpragma\\b"
                  ;
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = macroFormat;
        highlightingRules.append(rule);
    }

    color.setNamedColor(commentColor);
    brush.setColor(color);
    singleLineCommentFormat.setForeground(brush);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(brush);

    color.setNamedColor(stringColor);
    brush.setColor(color);
    quotationFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    color.setNamedColor(functionColor);
    brush.setColor(color);
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

///**
// * @brief Highlighter::CPPRule
// */
//void Highlighter::CPPRule()
//{
//    HighlightingRule rule;

//    keywordFormat.setForeground(Qt::darkBlue);
//    keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\b__asm\\b" << "\\bauto\\b" << "\\bbool\\b"
//                    << "\\bbreak\\b" << "\\bcase\\b" << "\\bcatch\\b"
//                    << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
//                    << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdelete\\b"
//                    << "\\bdo\\b"
//                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
//                    << "\\bexplicit\\b" << "\\bextern\\b" << "\\bfalse\\b"
//                    << "\\bfriend\\b" << "\\bfloat\\b"  << "\\bfor\\b"
//                    << "\\bgoto\\b"
//                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
//                    << "\\blong\\b" << "\\bnamespace\\b" << "\\bnew\\b"
//                    << "\\boperator\\b"
//                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
//                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
//                    << "\\bslots\\b" << "\\bsizeof\\b" << "\\bstatic\\b"
//                    << "\\bstruct\\b" << "\\bswitch\\b"
//                    << "\\btemplate\\b" << "\\bthis\\b" << "\\bthrow\\b"
//                    <<"\\btypedef\\b" << "\\btypename\\b" << "\\btrue\\b"
//                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
//                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
//                    << "\\breturn\\b"   ;
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = keywordFormat;
//        highlightingRules.append(rule);
//    }

//    keywordPatterns.clear();
//    macroFormat.setFontWeight(QFont::Bold);
//    macroFormat.setForeground(Qt::magenta);
//    keywordPatterns << "#\\binclude\\b" << "#\\bif\\b" << "#\\bifndef\\b"
//                  << "#\\belse\\b" << "#\\bendif\\b" << "#\\bdefine\\b"
//                  << "#\\bundef\\b" << "#\\bdefine\\b" << "#\\bpragma\\b"
//                  ;
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = macroFormat;
//        highlightingRules.append(rule);
//    }

//    classFormat.setFontWeight(QFont::Bold);
//    classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

//    singleLineCommentFormat.setForeground(Qt::red);
//    rule.pattern = QRegularExpression("//[^\n]*");
//    rule.format = singleLineCommentFormat;
//    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::red);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegularExpression("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegularExpression("/\\*");
//    commentEndExpression = QRegularExpression("\\*/");
//}

/**
 * @brief Highlighter::CPPRule
 * @param keywordColor
 * @param macroColor
 * @param commentColor
 * @param classColor
 * @param stringColor
 * @param functionColor
 */
void Highlighter::CPPRule(QString keywordColor = "darkblue", QString macroColor = "magenta", QString commentColor = "darkgreen", QString classColor = "darkmagenta", QString stringColor = "green", QString functionColor = "blue")
{
    QColor color(keywordColor);
    QBrush brush(color);
    HighlightingRule rule;
    keywordFormat.setForeground(brush);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\b__asm\\b" << "\\bbreak\\b" << "\\bcase\\b"
                    << "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
                    << "\\bdefault\\b" << "\\bdo\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
                    << "\\bextern\\b" << "\\bfloat\\b"  << "\\bfor\\b"
                    << "\\bgoto\\b"
                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
                    << "\\blong\\b" << "\\bshort\\b" << "\\bsigned\\b"
                    << "\\bsizeof\\b" << "\\bstatic\\b"
                    << "\\bstruct\\b" << "\\bswitch\\b"
                    <<"\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
                    << "\\breturn\\b"   ;
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    keywordPatterns.clear();
    color.setNamedColor(macroColor);
    brush.setColor(color);
    macroFormat.setFontWeight(QFont::Bold);
    macroFormat.setForeground(brush);
    keywordPatterns << "#\\binclude\\b" << "#\\bif\\b" << "#\\bifndef\\b"
                  << "#\\belse\\b" << "#\\bendif\\b" << "#\\bdefine\\b"
                  << "#\\bundef\\b" << "#\\bdefine\\b" << "#\\bpragma\\b"
                  ;
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = macroFormat;
        highlightingRules.append(rule);
    }

    color.setNamedColor(classColor);
    brush.setColor(color);
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    color.setNamedColor(commentColor);
    brush.setColor(color);
    singleLineCommentFormat.setForeground(brush);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(brush);

    color.setNamedColor(stringColor);
    brush.setColor(color);
    quotationFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    color.setNamedColor(functionColor);
    brush.setColor(color);
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(brush);
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

/**
 * @brief Highlighter::PythonRule
 * @param keywordColor
 * @param classColor
 * @param stringColor
 * @param functionColor
 */
void Highlighter::PythonRule(QString keywordColor = "darkblue", QString classColor = "magenta", QString commentColor = "red", QString stringColor ="darkcyan", QString functionColor ="blue")
{
    QColor color(keywordColor);
    QBrush brush(color);
    HighlightingRule rule;

    keywordFormat.setForeground(brush);
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

    color.setNamedColor(classColor);
    brush.setColor(color);
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    color.setNamedColor(commentColor);
    brush.setColor(color);
    singleLineCommentFormat.setForeground(brush);
    rule.pattern = QRegularExpression("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(brush);

    color.setNamedColor(stringColor);
    brush.setColor(color);
    quotationFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    color.setNamedColor(functionColor);
    brush.setColor(color);
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("'{3}|\"{3}");
    commentEndExpression = QRegularExpression("'{3}|\"{3}");
}

/**
 * @brief Highlighter::JavaRule
 * @param keywordColor
 * @param classColor
 * @param commentColor
 * @param stringColor
 * @param functionColor
 */
void Highlighter::JavaRule(QString keywordColor = "darkblue", QString classColor = "darkmagenta", QString commentColor = "green", QString stringColor ="darkgreen", QString functionColor = "blue")
{
    HighlightingRule rule;
    QColor color(keywordColor);
    QBrush brush(color);

    keywordFormat.setForeground(brush);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\babstract\\b" << "\\basser\\b" << "\\bboolean\\b"
                    << "\\bbreak\\b" << "\\bbyte\\b" << "\\bcase\\b" << "\\bcatch\\b"
                    << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdo\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
                    << "\\bextends\\b" << "\\bfloat\\b"  << "\\bfor\\b"
                    << "\\bfinal\\b" << "\\bfinally\\b"
                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
                    << "\\bimplements\\b" << "\\bimport\\b" << "\\binstanceof\\b"
                    << "\\binterface\\b"
                    << "\\blong\\b" << "\\bnative\\b" << "\\bnew\\b"
                    << "\\bpackage\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsigned\\b" <<"\\bswitch\\b"
                    << "\\bstatic\\b" << "\\bstrictfp\\b" << "\\bsuper\\b"
                    << "\\bsynchronized\\b"
                    << "\\bthis\\b" << "\\bthrow\\b" << "\\bthrows\\b"
                    << "\\btransient\\b"  << "\\btry\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
                    << "\\breturn\\b"   ;
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    color.setNamedColor(classColor);
    brush.setColor(color);
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    color.setNamedColor(commentColor);
    brush.setColor(color);
    singleLineCommentFormat.setForeground(brush);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(brush);

    color.setNamedColor(stringColor);
    brush.setColor(color);
    quotationFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    color.setNamedColor(functionColor);
    brush.setColor(color);
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(brush);
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

/**
 * @brief Highlighter::PythonRule
 */
//void Highlighter::PythonRule()
//{
//    HighlightingRule rule;

//    keywordFormat.setForeground(Qt::darkBlue);
//    keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\bFalse\\b" << "\\bNone\\b" << "\\bTrue\\b"
//                    << "\\band\\b" << "\\bas\\b" << "\\bassert\\b"
//                    << "\\bbreak\\b" << "\\bclass\\b" << "\\bcontinue\\b"
//                    << "\\bdef\\b" << "\\bdel\\b" << "\\belif\\b"
//                    << "\\belse\\b" << "\\bexcept\\b" << "\\bfinally\\b"
//                    << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
//                    << "\\bimport" << "\\bin\\b" << "\\bis\\b"
//                    << "\\blambda\\b" << "\\bnonlocal\\b" << "\\bnot\\b"
//                    << "\\bor\\b" << "\\bpass\\b" << "\\braise\\b"
//                    << "\\breturn\\b" << "\\btry\\b" << "\\bwhile\\b"
//                    << "\\bwith\\b" << "\\byield\\b" ;

//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = keywordFormat;
//        highlightingRules.append(rule);
//    }

//    classFormat.setFontWeight(QFont::Bold);
//    classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

//    singleLineCommentFormat.setForeground(Qt::red);
//    rule.pattern = QRegularExpression("#[^\n]*");
//    rule.format = singleLineCommentFormat;
//    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::red);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegularExpression("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegularExpression("'{3}|\"{3}");
//    commentEndExpression = QRegularExpression("'{3}|\"{3}");

//}

/**
 * @brief Highlighter::JavaRule
 */
//void Highlighter::JavaRule()
//{
//    HighlightingRule rule;

//    keywordFormat.setForeground(Qt::darkBlue);
//    keywordFormat.setFontWeight(QFont::Bold);
//    QStringList keywordPatterns;
//    keywordPatterns << "\\babstract\\b" << "\\basser\\b" << "\\bboolean\\b"
//                    << "\\bbreak\\b" << "\\bbyte\\b" << "\\bcase\\b" << "\\bcatch\\b"
//                    << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
//                    << "\\bcontinue\\b" << "\\bdefault\\b" << "\\bdo\\b"
//                    << "\\bdouble\\b" << "\\benum\\b" << "\\belse\\b"
//                    << "\\bextends\\b" << "\\bfloat\\b"  << "\\bfor\\b"
//                    << "\\bfinal\\b" << "\\bfinally\\b"
//                    << "\\binline\\b" << "\\bint\\b" << "\\bif\\b"
//                    << "\\bimplements\\b" << "\\bimport\\b" << "\\binstanceof\\b"
//                    << "\\binterface\\b"
//                    << "\\blong\\b" << "\\bnative\\b" << "\\bnew\\b"
//                    << "\\bpackage\\b"
//                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
//                    << "\\bshort\\b" << "\\bsigned\\b" <<"\\bswitch\\b"
//                    << "\\bstatic\\b" << "\\bstrictfp\\b" << "\\bsuper\\b"
//                    << "\\bsynchronized\\b"
//                    << "\\bthis\\b" << "\\bthrow\\b" << "\\bthrows\\b"
//                    << "\\btransient\\b"  << "\\btry\\b"
//                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bwhile\\b"
//                    << "\\breturn\\b"   ;
//    foreach (const QString &pattern, keywordPatterns) {
//        rule.pattern = QRegularExpression(pattern);
//        rule.format = keywordFormat;
//        highlightingRules.append(rule);
//    }

//    classFormat.setFontWeight(QFont::Bold);
//    classFormat.setForeground(Qt::darkMagenta);
//    rule.pattern = QRegularExpression("\\b[A-Z][A-Za-z]+\\b");
//    rule.format = classFormat;
//    highlightingRules.append(rule);

//    singleLineCommentFormat.setForeground(Qt::green);
//    rule.pattern = QRegularExpression("//[^\n]*");
//    rule.format = singleLineCommentFormat;
//    highlightingRules.append(rule);

//    multiLineCommentFormat.setForeground(Qt::green);

//    quotationFormat.setForeground(Qt::darkGreen);
//    rule.pattern = QRegularExpression("\".*\"");
//    rule.format = quotationFormat;
//    highlightingRules.append(rule);

//    functionFormat.setFontItalic(true);
//    functionFormat.setForeground(Qt::blue);
//    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
//    rule.format = functionFormat;
//    highlightingRules.append(rule);

//    commentStartExpression = QRegularExpression("/\\*");
//    commentEndExpression = QRegularExpression("\\*/");
//}

/**
 * @brief Highlighter::MakeRule
 */
void Highlighter::MakeRule()
{

}

/**
 * @brief Highlighter::setupRule
 */
void Highlighter::setupRule()
{
    // CPPRule();
    PythonRule();

}

/**
 * @brief Highlighter::setupRule
 * @param extension
 */
void Highlighter::setupRule(QString extension)
{
    deleteRule();
    QString lExtension = extension.toLower();
    if(lExtension == "py"){
        PythonRule();
    }
    else if (extension == "c") {
        CRule();
    }
    else if (lExtension == "h" || extension == "hpp" || extension == "cpp") {
        CPPRule();
    }
    else if (lExtension == "java" || extension == "class"){
        JavaRule();
    }
}
