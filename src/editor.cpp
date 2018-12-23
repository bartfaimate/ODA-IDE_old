#include <QtWidgets>
#include <string>

#include "Headers/editor.h"
#include "Headers/highlighter.h"
//![constructor]
Editor::Editor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLineWrapper()));
    //connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(getLineIndent()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLineWrapper();
    //  setFontSettings("Courier", 12, 4);
    setFontSettings();
    // this->setStyleSheet("background-color: gray");

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
    QSettings settings(QString("configs/settings.ini"), QSettings::IniFormat); /* load settings */
    /* setup window position and size */
    QString fontType = settings.value("Editor/font_type").toString();
    int fontSize = settings.value("Editor/font_size").toInt();
    font = new QFont();
    font->setFamily(fontType);
    font->setStyleHint(QFont::Monospace);
    font->setFixedPitch(true);
    font->setPointSize(fontSize);
    this->setFont(*font);

    const int tabStop = 4;
    metrics = new QFontMetrics(*font);
    this->setTabStopWidth(tabStop * metrics->width(" "));
    this->tabWidth = tabStop;
}

void Editor::setFontSettings(QString fontFamily, int fontSize, int tabWidth = 4)
{
    font = new QFont();
    font->setFamily(fontFamily);
    font->setStyleHint(QFont::Monospace);
    font->setFixedPitch(true);
    font->setPointSize(fontSize);
    this->setFont(*font);

    metrics = new QFontMetrics(*font);
    this->setTabStopWidth(tabWidth * metrics->width(" "));
    this->tabWidth = tabWidth;
}


/**
 * @brief Editor::setFontSettings
 * @param fontFaimily
 * @param tabwidth
 */
void Editor::setFontSettings(QString fontFaimily, int tabwidth = 4)
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
    this->tabWidth = tabwidth;
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

void Editor::openFile(QString fileName)
{
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QErrorMessage *fileError = new QErrorMessage();
        fileError->showMessage(tr("ERROR by opening file"));
    }

    Highlighter *currentHighlighter = new Highlighter(this->document());
    this->setFileNameAndExtension(fileName);
    currentHighlighter->setupRule(this->getFileExtension());

    QString info = ">> " + fileName + " opened\n";

    QTextStream *readFile = new QTextStream(file);
    this->document()->setPlainText(readFile->readAll());
    file->flush();
    file->close();
    emit(this->filenameChanged(fileName));
}

void Editor::saveFile(QString fileName)
{

}

void Editor::newFile(QString fileName)
{
    QFile *file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QErrorMessage *fileError = new QErrorMessage();
        fileError->showMessage(tr("ERROR by saving"));
        return;
    }
    this->setFileNameAndExtension(fileName);
    Highlighter *currentHighlighter = new Highlighter(this->document());
    currentHighlighter->setupRule(this->getFileExtension());

    this->clear();
    file->close();
}



/**
 * @brief Editor::getLightenValue
 * @return
 */
int Editor::getLightenValue()
{
    return this->lightenValue;
}

/**
 * @brief Editor::setLightenValue
 * @param lighten
 */
void Editor::setLightenValue(int lighten)
{
    this->lightenValue = lighten;
}

/**
 * @brief Editor::getHighlightColor
 * @return
 */
QString Editor::getHighlightColor()
{
    return this->highlightColor;
}

/**
 * @brief Editor::setHighlightColor
 * @param color
 */
void Editor::setHighlightColor(QString color)
{
    this->highlightColor = color;
}

/**
 * @brief Editor::setFontFamily
 * @param fontFamily
 */
void Editor::setFontFamily(QString fontFamily)
{
    this->fontFamily = fontFamily;
}

/**
 * @brief Editor::getFontFamily
 * @return
 */
QString Editor::getFontFamily()
{
    return this->fontFamily;
}

/**
 * @brief Editor::setTabWidth
 * @param tabWidth
 */
void Editor::setTabWidth(int tabWidth)
{
    this->tabWidth = tabWidth;
}

/**
 * @brief Editor::getTabWidth
 * @return
 */
int Editor::getTabWidth()
{
    return this->tabWidth;
}

/**
 * @brief Editor::setFontSize
 * @param fontSize
 */
void Editor::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
}

/**
 * @brief Editor::getFontSize
 * @return
 */
int Editor::getFontSize()
{
    return this->fontSize;
}

//![slotUpdateRequest]

//![resizeEvent]

void Editor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

int Editor::getLineIndent()
{
    QString currentLine;
    int lineIndent = 0;
    if(!isReadOnly()) {
        currentLine = this->textCursor().block().text().trimmed();
        std::string asciCurrentLine = currentLine.toStdString();
        for(int i = 0; i < asciCurrentLine.length(); i++) {
            switch(asciCurrentLine[i]) {
            case ' ':
                lineIndent++;
                break;
            case '\t':
                lineIndent += this->tabWidth;
                break;
            default:

                break;
            }
        }
    }
    return lineIndent;
}

/* TODO: ezt meg kell csinálni nagyon nem jó */
int Editor::getLineIndent(int row)
{
    QCursor *cursor = new QCursor();
    int rowPos = cursor->pos().y();
    int colPis = cursor->pos().x();


    QString currentLine;
    int lineIndent = 0;

    currentLine = this->textCursor().block().text().trimmed();
    std::string asciCurrentLine = currentLine.toStdString();
    for(int i = 0; i < asciCurrentLine.length(); i++) {
        switch(asciCurrentLine[i]) {
        case ' ':
            lineIndent++;
            break;
        case '\t':
            lineIndent += this->tabWidth;
            break;
        default:

            break;
        }
    }

    return lineIndent;
}

long Editor::lineCount()
{
    return this->document()->lineCount();
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

/**
 * @brief Editor::highlightCurrentLine
 * @param highlightColor
 */
void Editor::highlightCurrentLine(QString highlightColor, int lighten = 160)
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(highlightColor).lighter(lighten);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

/**
 * @brief Editor::highlightCurrentLineWrapper
 */
void Editor::highlightCurrentLineWrapper()
{
    highlightCurrentLine("gray", 180);
}

//![cursorPositionChanged]

//![extraAreaPaintEvent_0]

void Editor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    //![extraAreaPaintEvent_0]QString highlightColor;

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
