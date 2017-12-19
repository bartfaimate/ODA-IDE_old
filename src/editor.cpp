#include <QtWidgets>

#include "Headers/editor.h"

//![constructor]

Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    setFontSettings();
}

//![constructor]

//![extraAreaWidth]
/**
 * @brief Editor::lineNumberAreaWidth
 * @return
 */
int Editor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

/**
 * @brief Editor::setFontSettings
 */
void Editor::setFontSettings()
{
    font = new QFont();
    font->setFamily("Courier");
    font->setStyleHint(QFont::Monospace);
    font->setFixedPitch(true);
    font->setPointSize(10);
    this->setFont(*font);

    const int tabStop = 4;
    metrics = new QFontMetrics(*font);
    this->setTabStopWidth(tabStop * metrics->width(" "));
}

/**
 * @brief Editor::setFontSettings
 * @param fontFaimily
 * @param tabwidth
 */
void Editor::setFontSettings(QString fontFaimily, int tabwidth)
{
    font = new QFont();
    font->setFamily(fontFaimily);
    font->setStyleHint(QFont::Monospace);
    font->setFixedPitch(true);
    font->setPointSize(10);

    const int tabStop = tabwidth;
    metrics = new QFontMetrics(*font);
    this->setTabStopWidth(tabStop * metrics->width(" "));
    this->setFont(*font);
}

/**
 * @brief Editor::setFileExtension
 * @param fileName
 */
void Editor::setFileExtension()
{
    QRegularExpression regexp("(.)([a-zA-z0-9]+)$");
    QRegularExpressionMatch match = regexp.match(this->openedFileName);
    if(match.hasMatch()){
        this->fileExtension = match.captured(2);
    }
}

QString Editor::getFileExtension()
{
    return this->fileExtension;
}

/**
 * @brief Editor::getOpenedFileName
 * @return the filename the actual editor
 */
QString Editor::getOpenedFileName()
{
    return this->openedFileName;
}

/**
 * @brief Editor::getShortFileName
 * @return
 */
QString Editor::getShortFileName()
{
    QString pattern = "((\\w)+(\\.)?(\\w)+)$";   //ok but filename with 2 dots not working
    QRegularExpression regEx(pattern);
    QRegularExpressionMatch match = regEx.match(this->openedFileName);
    QString matched;
    if (match.hasMatch()) {
        matched = match.captured(1);    //
    }
    else {
        matched = " ";
    }
    return matched;
}

/**
 * @brief Editor::setOpenedFileName
 * @param openedFileName
 */
void Editor::setOpenedFileName(QString openedFileName)
{
    this->openedFileName = openedFileName;
}

void Editor::setFileNameAndExtension(QString openedFileName)
{
    setOpenedFileName(openedFileName);
    setFileExtension();
}

//![extraAreaWidth]

//![slotUpdateExtraAreaWidth]

void Editor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

//![slotUpdateExtraAreaWidth]

//![slotUpdateRequest]

void Editor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

//![slotUpdateRequest]

//![resizeEvent]

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

//![resizeEvent]

//![cursorPositionChanged]

void Editor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

//![extraAreaPaintEvent_0]

//![extraAreaPaintEvent_1]
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
//![extraAreaPaintEvent_1]

//![extraAreaPaintEvent_2]
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
//![extraAreaPaintEvent_2]
