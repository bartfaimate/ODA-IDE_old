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
#include "settings.h"

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


    QList<QString> *openedFiles;

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
    QPushButton *undoButton;
    QPushButton *newWindowButton;
    QPushButton *compileButton;
    QPushButton *runButton;

    /* icons */
    QIcon *newTabIcon = new QIcon("./img/gnome-icons/add.svg");
    QIcon *newFileIcon = new QIcon("./img/gnome-icons/document-new.svg");
    QIcon *saveIcon = new QIcon("./img/gnome-icons/document-save.png");
    QIcon *saveAsIcon = new QIcon("./img/gnome-icons/document-save-as.png");
    QIcon *openIcon = new QIcon("./img/gnome-icons/document-open.svg");

    QIcon *buildIcon = new QIcon("./img/gnome-icons/build.png");
    QIcon *runIcon = new QIcon("./img/gnome-icons/run.png");

    QIcon *undoIcon = new QIcon("./img/gnome-icons/edit-undo.svg");
    QIcon *redoIcon = new QIcon("./img/gnome-icons/edit-redo.svg");
    QIcon *copyIcon = new QIcon("./img/gnome-icons/edit-copy.png");
    QIcon *pasteIcon = new QIcon("./img/gnome-icons/edit-paste.png");
    QIcon *cutIcon = new QIcon("./img/gnome-icons/edit-cut.png");

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
    void openSettingsWindow();

};


#endif // MAINWINDOW_H
