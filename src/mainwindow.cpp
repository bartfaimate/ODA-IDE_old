#include "Headers/mainwindow.h"
//#include <ui_mainwindow.h>

#include <iostream>
#include <QTextStream>
#include <QErrorMessage>
#include <QFileDialog>
#include <QScreen>
#include <QGuiApplication>

#include <thread>

using namespace std;

#define DEBUG 1

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * constructor. Sets up window layout, creats buttons, menus, tabwidget
 * creates buttons and add actions and opens window in the last opened size
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //window(new Ui::MainWindow)
{

    createLayout();     /* crete layout, positions items, splitter */
    createActions();    /* create actions for the buttons */
    createMenus();      /* create menus  */
    createButtons();    /* create buttons */
    if (tab != NULL){
        setupTabs();
    }

    QSettings settings(QString("configs/config.ini"), QSettings::IniFormat); /* load settings */
    /* setup window position and size */
    int x = settings.value("window/xpos").toInt();
    int y = settings.value("window/ypos").toInt();
    int width = settings.value("window/width").toInt();
    int height = settings.value("window/height").toInt();

    /* window size and position */
    this->setGeometry(x, y+24, width, height); /* window size and position */
    this->setWindowTitle(tr("ODA-IDE")); /* setup title */
    createStatusbar(20);

    /* setup window icon */
    QIcon *windowIcon = new QIcon("./img/icon.png");
    this->setWindowIcon(*windowIcon);

    this->console->setup();
#if DEBUG == 1
    this->console->appendDebuginfo("Debug mode started");
#endif

}

/**
 * @brief MainWindow::~MainWindow
 * destructor
 */
MainWindow::~MainWindow()
{
    saveGeometry();
    saveSettings();

    delete this;
}

/**
 * @brief MainWindow::addTab
 * add a new tab with editor and setup the current tab index
 */
void MainWindow::addTab()
{
    Editor *tabeditor = new Editor();   /* new editor in tab */
    Highlighter *tabhighlighter = new Highlighter(tabeditor->document());   /* setup synta highlight */
    this->tab->addTab(tabeditor, tr("(new)"));      /* setup tab title */
    tab->setCurrentIndex(tab->count() - 1);         /* set current index, make it active */

#if DEBUG == 1
    cout << "tabsnum:" << tab->count()<<endl;
#endif
}

/**
 * @brief MainWindow::createLayout
 * Creates layout with tabwidget, output console, splitter. Editor is in separated tabs
 */
void MainWindow::createLayout()
{
    /* widget is mainwidget*/
    QWidget *mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    hBoxLayout = new QHBoxLayout(); /* horizontal layout */

    verticalSplitter = new QSplitter(); /* vertical splitter for the file system view */
    verticalSplitter->setOrientation(Qt::Vertical);
    horizontalSplitter = new QSplitter(Qt::Horizontal); /* horizontal splitter for the debug console and text editor */

    menuBar = new QMenuBar();
    toolBar = new QToolBar();

    menuBar = new QMenuBar(topFiller);  /* menubar to the top */
    toolBar = new QToolBar(topFiller);  /* toolbar to the top, under menubar */

    console = new Console();
    //tab = new QTabWidget();

   //TODO: this is not working yet
    fileManager = new FileManager();
    horizontalSplitter->addWidget(fileManager);
    horizontalSplitter->addWidget(verticalSplitter);
    tab =  new Tab();       /* tab widget to the splitter */
    verticalSplitter->addWidget(tab);
    verticalSplitter->addWidget(console);   /* console under the tab */

//most jó a file menü gomb, viszont splitter nem
    QVBoxLayout *vBoxLayout = new QVBoxLayout(); /* vertical layout */
    vBoxLayout->setMargin(5);
    vBoxLayout->addWidget(menuBar);
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->addWidget(verticalSplitter);
 //   vBoxLayout->addWidget(tab);

    mainWidget->setLayout(vBoxLayout);
    hBoxLayout->addWidget(toolBar);
    this->setLayout(hBoxLayout);
    this->addTab();      /* add the first tab with editor */

}

/**
 * @brief MainWindow::createMenus
 * creates menus
 */
void MainWindow::createMenus()
{
    createFileMenu();
    createEditMenu();
    createCompileMenu();
    createHelpMenu();
}

/**
 * @brief MainWindow::createFileMenu
 * creates file menu and elements
 */
void MainWindow::createFileMenu()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newWindowAct);
    fileMenu->addAction(newTabAct);
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(saveFileAct);
    fileMenu->addAction(saveFileAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

/**
 * @brief MainWindow::createEditMenu
 * creates edit menu and elements
 */
void MainWindow::createEditMenu()
{
    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
}

/**
 * @brief MainWindow::createCompileMenu
 */
void MainWindow::createCompileMenu()
{
    compilerMenu = menuBar->addMenu(tr("Com&piler"));
    compilerMenu->addAction(compileAct);
    compilerMenu->addAction(buildAct);
    compilerMenu->addAction(makeAct);
    compilerMenu->addSeparator();
    compilerMenu->addAction(buildSettingsAct);
}

/**
 * @brief MainWindow::createHelpMenu
 */
void MainWindow::createHelpMenu()
{
    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

/**
 * @brief MainWindow::createButtons
 * creates buttons for the toolbar
 */
void MainWindow::createButtons()
{
    /*NEW TAB*/
    newTabButton = new QPushButton(*newTabIcon, tr(""));
    toolBar->addWidget(newTabButton);
    connect(newTabButton, SIGNAL(clicked(bool)), this, SLOT(addTab()));
    newTabButton->setToolTip(tr("New tab"));

    /* NEW FILE*/
    newFileButton = new QPushButton(*newFileIcon, tr(""));
    toolBar->addWidget(newFileButton);
    connect(newFileButton, SIGNAL(clicked(bool)), this, SLOT(newFile()));
    newFileButton->setToolTip(tr("Create new file"));

    /*SAVE*/
    saveButton = new QPushButton(*saveIcon, tr(""));
    toolBar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    saveButton->setToolTip(tr("Save current file"));

    /* UNDO */
    undoButton = new QPushButton(*undoIcon, tr(""));
    toolBar->addWidget(undoButton);
    connect(undoButton, SIGNAL(clicked(bool)), tab, SLOT(undo()));
    undoButton->setToolTip(tr("Undo"));

    compileButton = new QPushButton(*buildIcon, tr(""));
    toolBar->addWidget(compileButton);
    compileButton->setToolTip(tr("Compile"));

    runButton = new QPushButton(*runIcon, tr(""));
    toolBar->addWidget(runButton);
    runButton->setToolTip(tr("Run"));
}

/**
 * @brief MainWindow::createActions
 * This function creates menu elements and actions for them.
 */
void MainWindow::createActions()
{
    createFileActions();
    createEditActions();
    createCompileActions();
    createHelpActions();
}

/**
 * @brief MainWindow::createFileActions
 * creates actions for the file menu
 */
void MainWindow::createFileActions()
{
    newWindowAct = new QAction(tr("&New Window"), this);
    newWindowAct->setShortcuts(QKeySequence::New);
    newWindowAct->setStatusTip(tr("Create a new window"));
    connect(newWindowAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

    newTabAct = new QAction(*newTabIcon, tr("New &Tab"), this);
    newTabAct->setShortcuts(QKeySequence::AddTab);
    newTabAct->setStatusTip(tr("Create new tab"));
    connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(addTab()));

    newFileAct = new QAction(*newFileIcon, tr("New F&ile"), this);
    newFileAct->setStatusTip(tr("Create new File"));
    connect(newFileAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openFileAct = new QAction(*openIcon, tr("&Open File"), this);
    openFileAct->setShortcut(QKeySequence::Open);
    openFileAct->setStatusTip(tr("Open existing File"));
    connect(openFileAct, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    saveFileAct = new QAction(*saveIcon, tr("&Save"), this);
    saveFileAct->setShortcut(QKeySequence::Save);
    saveFileAct->setStatusTip(tr("Save a file"));
    connect(saveFileAct, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    saveFileAsAct = new QAction(*saveAsIcon, tr("Save as"), this);
    saveFileAsAct->setShortcut(QKeySequence::SaveAs);
    saveFileAsAct->setStatusTip(tr("Save as file"));
    connect(saveFileAsAct, SIGNAL(triggered(bool)), this, SLOT(saveAsFile()));

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Close current window"));
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(close()));
}

/**
 * @brief MainWindow::createEditActions
 * creates actions for the edit menu
 */
void MainWindow::createEditActions()
{
   // Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());

    undoAct = new QAction(*undoIcon, tr("Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered(bool)), tab, SLOT(undo()));

    redoAct = new QAction(*redoIcon, tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered(bool)), tab, SLOT(redo()));

    copyAct = new QAction(*copyIcon, tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    connect(copyAct, SIGNAL(triggered(bool)), tab, SLOT(copy()));

    cutAct = new QAction(*cutIcon, tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    connect(cutAct, SIGNAL(triggered(bool)), tab, SLOT(cut()));

    pasteAct = new QAction(*pasteIcon, tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    connect(pasteAct, SIGNAL(triggered(bool)), tab, SLOT(paste()));
}

/**
 * @brief MainWindow::createCompileActions
 * creates actions for the compiler menu
 */
void MainWindow::createCompileActions()
{
    compileAct = new QAction(tr("Compile"), this);

    buildAct = new QAction(tr("Build"), this);

    makeAct = new QAction(tr("Make"), this);

    buildSettingsAct = new QAction(tr("Build Settings"), this);
    buildSettingsAct->setStatusTip(tr("Open settings window"));
    connect(buildSettingsAct, SIGNAL(triggered(bool)), this, SLOT(openSettingsWindow()));
}

/**
 * @brief MainWindow::createHelpActions
 * cretes actions for the help menu
 */
void MainWindow::createHelpActions()
{
    aboutAct = new QAction(tr("About"), this);

    aboutQtAct = new QAction(tr("About Qt"), this);
}

/**
 * @brief MainWindow::createStatusbar
 * @param height is the hieght of the statusbar
 */
void MainWindow::createStatusbar(int height)
{
    statusBar()->setMaximumHeight(height);
    statusBar()->setMaximumHeight(height);
    statusBar()->showMessage(tr("Started"), 2000);
}

/**
 * @brief MainWindow::loadSettings
 */
void MainWindow::loadSettings()
{
    /*TODO: finish this*/
}

/**
 * @brief MainWindow::openSettingsWindow
 */
void MainWindow::openSettingsWindow()
{
    Settings *settings = new Settings();
    settings->show();
}

/**
 * @brief MainWindow::openFile
 */
void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), tr("All files(*)"));

    if(filename.isEmpty()){
        return;
    }
    else{
        QFile *file = new QFile(filename);

        try{
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
                QErrorMessage *fileError = new QErrorMessage();
                fileError->showMessage(tr("ERROR by opening file"));
            }

            /* cast QWidget to Editor */
            Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());
            Highlighter *currentHighlighter = new Highlighter(currentEditor->document());
            currentEditor->setFileNameAndExtension(filename);
            currentHighlighter->setupRule(currentEditor->getFileExtension());

            QString info = ">> " + filename + " opened\n";
            console->appendPlainText(info);
            statusBar()->showMessage(currentEditor->getFileExtension());
#if DEBUG == 1
            cout <<  currentEditor->getOpenedFileName().toStdString() << endl;
            cout <<  currentEditor->getFileExtension().toStdString() << endl;
#endif
            QTextStream *readFile = new QTextStream(file);
            currentEditor->document()->setPlainText(readFile->readAll());
            file->flush();
            file->close();
            emit(currentEditor->filenameChanged(filename));
            tab->setTabText(tab->currentIndex(), currentEditor->getShortFileName());

        }
        catch (...){
            cout << "error opening file" << endl;
            console->appendDebuginfo("[OPENFILE]: error opening file");
            try {
                file->close();
            }
            catch(...) {
                cout << "[OPEN:] file close error" <<endl;
                console->appendDebuginfo("[OPENFILE]: error closing file");
            }
        }
    }
}


/**
 * @brief MainWindow::newWindow
 * creates new window
 */
void MainWindow::newWindow()
{
    newWindows = new MainWindow();
    newWindows->show();
}

/**
 * @brief MainWindow::newFile
 * create new empty file
 */
void MainWindow::newFile()
{
#if DEBUG == 1
    cout << "new file" << endl;
#endif
    QString filename = QFileDialog::getSaveFileName(this, tr("New File"), tr("All files(*)"));
    if(filename.isEmpty()){
        return;
    }
    QFile *file = new QFile(filename);

    try{
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
            QErrorMessage *fileError = new QErrorMessage();
            fileError->showMessage(tr("ERROR by saving"));
            return;
        }
        Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());
        currentEditor->setFileNameAndExtension(filename);
        QString info = ">> " + filename + " created\n";
        console->appendPlainText(info);
        statusBar()->showMessage(currentEditor->getFileExtension());

        currentEditor->clear();
        file->close();
        if(!Editor(tab->currentWidget()).document()->isEmpty()){
            addTab();
            tab->setCurrentIndex(tab->count()-1);
        }
        emit(currentEditor->filenameChanged(filename));

#if DEBUG == 1
        cout << filename.toStdString() << endl;
        console->appendDebuginfo(filename);
        console->appendDebuginfo(currentEditor->getFileExtension());
#endif
    }
    catch(...){
        QErrorMessage *fileError = new QErrorMessage();
        fileError->showMessage(tr("ERROR by saving"));
        try{
            file->close();
        }
        catch(...){
            cout << "[NEW FILE:] file close error" << endl;
            console->appendDebuginfo("[NEWFILE]: error closing file");
        }
    }
}

/**
 * @brief MainWindow::saveAsFile
 * creates a new file and saves the content of the editor
 */
void MainWindow::saveAsFile()
{
    /* filename to be saved */
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As File"), tr("All files(*)"));

    if(filename.isEmpty()) {
        return;
    }

    /* file object */
    QFile *file = new QFile(filename);
    try{
        if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
            QErrorMessage *fileError = new QErrorMessage();
            fileError->showMessage(tr("ERROR by saving"));
            return;
        }
        /* cast the curent tab to Editor */
        Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());
        currentEditor->setFileNameAndExtension(filename);   /* editor filename and filetype setup */
        Highlighter *currentHighlighter = new Highlighter(currentEditor->document());
        currentHighlighter->setupRule(currentEditor->getFileExtension());

        QString info = ">> " + filename + " saved\n";
        console->appendPlainText(info);                     /* print the file name in the console */
        statusBar()->showMessage(currentEditor->getFileExtension());    /* show the file extension in the statusbar */

        file->write(currentEditor->toPlainText().toStdString().c_str()); /* write text to the file */
        file->flush();
        file->close();
        emit(currentEditor->filenameChanged(filename));
        tab->setTabText(tab->currentIndex(), currentEditor->getShortFileName());

    }
    catch(...){
        QErrorMessage *fileError = new QErrorMessage();
        fileError->showMessage(tr("ERROR by saving"));
        try{
            file->close();
        }
        catch(...){
            cout << "[SAVE AS:] file close error" << endl;
            this->console->appendDebuginfo("[SAVE AS:] file close error");
        }
    }
}

/**
 * @brief MainWindow::saveFile
 */
void MainWindow::saveFile()
{
    /* cast current widget to editor */
    Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());
    QString filename = currentEditor->getOpenedFileName();

    /* if filename is empty save as file else just save file */
    if(filename.isEmpty()){
        this->saveAsFile();
    }
    else{
        QFile *file = new QFile(filename);
        try{
            if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
                QErrorMessage *fileError = new QErrorMessage();
                fileError->showMessage(tr("ERROR by saving"));
                return;
            }
           // while(file->readLine() != EOF)

            file->write(currentEditor->toPlainText().toStdString().c_str());
            file->flush();
            file->close();
        }
        catch(...){
            QErrorMessage *fileError = new QErrorMessage();
            fileError->showMessage(tr("ERROR by saving"));
            try{
                file->close();
            }
            catch(...){
                cout << "[SAVE:] file close error" << endl;
            }
        }
    }
}

/**
 * @brief MainWindow::saveGeometry
 */
void MainWindow::saveGeometry()
{
    qDebug() << "savegeometry\n";
}

/**
 * @brief MainWindow::saveSettings
 */
void MainWindow::saveSettings()
{
    //TODO: ezt befejezni
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    QSettings settings(QString("configs/config.ini"), QSettings::IniFormat);
    bool isFullSize = false;
    int xpos = this->x();
    int ypos = this->y();
    int height = this->height();
    int width = this->width();
    int screenHeight = screenGeometry.height();
    int screenWidth = screenGeometry.width();

    settings.setValue("window/xpos", xpos);
    settings.setValue("window/ypos", ypos);
    settings.setValue("window/height", height);
    settings.setValue("window/width", width);
    settings.setValue("window/mode", isFullSize);
    settings.setValue("theme", "default.css");

    settings.setValue("screen/height", screenHeight);
    settings.setValue("screen/width", screenWidth);


    qDebug() << "height:" << height;
    qDebug() << "width:" << width;
    qDebug() << "screen height:" << screenHeight;
    qDebug() << "screen width:" << screenWidth;

    delete screen;

}

/**
 * @brief MainWindow::setupTabs
 */
void MainWindow::setupTabs()
{
    tab->setTabsClosable(true);
    tab->setMovable(true);

    connect(tab, SIGNAL(tabCloseRequested(int)), tab, SLOT(closeTab(int)));

}
