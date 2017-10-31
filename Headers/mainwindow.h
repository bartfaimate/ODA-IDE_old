#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QSplitter>
#include "editor.h"
#include "console.h"
#include "highlighter.h"

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

    Editor *editor;     /* Code editor section */
    Console *console;   /* Console output */
    Highlighter *highlighter; /* Syntax highlighter */

    QHBoxLayout *hBoxLayout;
    QSplitter *verticalSplitter;
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
    QAction *pasteAct;
    /*compiler menu*/
    QAction *compileAct;
    QAction *buildAct;
    QAction *makeAct;
    QAction *buildSettingsAct;
    /*help menu*/
    QAction *aboutAct;
    QAction *aboutQtAct;

    MainWindow *newWindows;

private:
    void createMenus();
    void createFileMenu();
    void createEditMenu();
    void createCompileMenu();
    void createHelpMenu();

    void createActions();
    void createFileActions();
    void createEditActions();
    void createCompileActions();
    void createHelpActions();
    void createStatusbar(int height);



public slots:
    void newWindow();
    void newFile();
    void saveFile();
    void saveAsFile();
    void openFile();

};


#endif // MAINWINDOW_H