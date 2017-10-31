#include "Headers/console.h"

Console::Console(QWidget *parent) :  QPlainTextEdit(parent)
{

}

/**
 * @brief Console::setup
 */
void Console::setup()
{
    this->setReadOnly(true);
    this->clearConsole();
    this->appendConsoleLog("Application started\n");
}

/**
 * @brief Console::AppendConsoleLog
 * @param msg
 */
void Console::appendConsoleLog(QString msg)
{
    this->appendPlainText(msg);
}

/**
 * @brief Console::clearConsole
 */
void Console::clearConsole()
{
    this->clear();
}

/**
 * @brief Console::appendDebuginfo
 * @param msg
 */
void Console::appendDebuginfo(QString msg)
{
    this->appendPlainText(tr("[DEBUG]: "));
    this->appendPlainText(msg);
    this->appendPlainText(tr("\n"));
}
