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
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
class Highlighter;
class Editor;
class Tab;
class SettingsDialog;
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
    QString title = tr("ODA-IDE");
    QString iconPath = "./icons/1x/";

    QString settingsPath = "configs/settings.ini";


    QList<QString> *openedFiles;

    Ui::MainWindow *window;

    //Editor *editor;     /* Code editor section */
    Console *console;   /* Console output */
    Highlighter *highlighter; /* Syntax highlighter */
    FileManager *fileManager;
    Tab *tab;
    SettingsDialog *settingsDialog;

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
    QIcon *newTabIcon = new QIcon(iconPath + "baseline_add_black_48dp.png");
    QIcon *newFileIcon = new QIcon(iconPath + "baseline_insert_drive_file_black_48dp.png");
    QIcon *saveIcon = new QIcon(iconPath + "baseline_save_black_48dp.png");
    QIcon *saveAsIcon = new QIcon(iconPath + "baseline_save_alt_black_48dp.png");
    QIcon *openIcon = new QIcon("./img/gnome-icons/document-open.svg");

    QIcon *buildIcon = new QIcon(iconPath + "baseline_build_black_48dp.png");
    QIcon *runIcon = new QIcon(iconPath + "baseline_play_arrow_black_48dp.png");

    QIcon *undoIcon = new QIcon(iconPath + "baseline_undo_black_48dp.png");
    QIcon *redoIcon = new QIcon(iconPath + "baseline_redo_black_48dp.png");
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
    QAction *newProjectAct;
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
    QAction *runAct;
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
    void newProject();
    void saveFile();
    void saveAsFile();
    void openFile();
    void addTab();
    void saveGeometry();
    void saveSettings();
    void loadSettings();
    void openSettingsWindow();

    void updateSettings();

};


#endif // MAINWINDOW_H
