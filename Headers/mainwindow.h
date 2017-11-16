#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QDebug>
#include <QSettings>

#include "editor.h"
#include "console.h"
#include "highlighter.h"
#include "tab.h"
#include "filemanager.h"

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

    QString companyName = "OI";
    QString appName = "ODA-IDE";

    Ui::MainWindow *window;

    //Editor *editor;     /* Code editor section */
    Console *console;   /* Console output */
    Highlighter *highlighter; /* Syntax highlighter */
    FileManager *fileManager;
    Tab *tab;

    QHBoxLayout *hBoxLayout;
    QSplitter *verticalSplitter;
    QSplitter *horizontalSplitter;
    QMenuBar *menuBar;
    QToolBar *toolBar;

    /* toolbar buttons */
    QPushButton *newFileButton;
    QPushButton *newTabButton;
    QPushButton *saveButton;
    QPushButton *newWindowButton;
    QPushButton *compileButton;
    QPushButton *runButton;

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
    void createLayout();
    void createMenus();
    void createFileMenu();
    void createEditMenu();
    void createCompileMenu();
    void createHelpMenu();
    void createButtons();

    void setupTabs();


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
    void addTab();
    void saveGeometry();
    void saveSettings();
    void loadSettings();

};


#endif // MAINWINDOW_H
