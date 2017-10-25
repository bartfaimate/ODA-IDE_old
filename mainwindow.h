#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "editor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *window;

    Editor *editor; /* Code editor section */
    QHBoxLayout *hBoxLayout;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    /* menus */
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *compilerMenu;
    /*file menu*/
    QAction *newWindowAct;
    QAction *newTabAct;
    QAction *newFileAct;

    QAction *openFileAct;
    QAction *saveFileAct;
    QAction *saveFileAsAct;

    QAction *printAct;
    QAction *exitAct;
    /*edit menu*/
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    /*compiler menu*/
    QAction *compileAct;
    QAction *buildAct;
    QAction *makeAct;
    QAction *buildSettingsAct;
    /*help menu*/
    QAction *aboutAct;
    QAction *aboutQtAct;

    MainWindow *newWindows;

    void createMenus();
    void createActions();

public slots:
    void newWindow();

};


#endif // MAINWINDOW_H
