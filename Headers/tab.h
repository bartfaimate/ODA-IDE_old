#ifndef TAB_H
#define TAB_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QSplitter>

#include "editor.h"
#include "highlighter.h"


class TabContent : public QWidget
{
public:
    TabContent(QWidget *parent = 0);

    ~TabContent();

private:

    Editor *editor;     /* Code editor section */
    Highlighter *highlighter; /* Syntax highlighter */

public slots:
};

#endif // TAB_H
