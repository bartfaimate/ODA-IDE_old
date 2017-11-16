#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>

/**
 * @brief The Console class
 * this class the output console under the Editor widget.
 */
class Console :  public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

signals:

public slots:
    void setup();
    void appendConsoleLog(QString msg);
    void clearConsole();
    void appendDebuginfo(QString msg);

};

#endif // CONSOLE_H
