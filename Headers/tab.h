#ifndef TAB_H
#define TAB_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QSplitter>

#include "editor.h"
#include "highlighter.h"


class Tab : public QTabWidget
{

     Q_OBJECT
public:
   // Tab(QWidget *parent = 0);

    ~Tab();

private:

public slots:
    void closeTab(int index);
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
};

#endif // TAB_H
