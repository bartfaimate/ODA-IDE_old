#include "Headers/mainwindow.h"
//#include <ui_mainwindow.h>

#include <iostream>
#include <QTextStream>
#include <QErrorMessage>
#include <QFileDialog>


using namespace std;

#define DEBUG 1

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //window(new Ui::MainWindow)
{

    createLayout();
    createActions();
    createMenus();
    createButtons();
    if (tab != NULL){
        setupTabs();
    }

    QSettings settings(QString("configs/config.ini"), QSettings::IniFormat);
  // settings->setValue("window/xpos", 50);
  // settings->setValue("window/ypos", 50);
  // settings->setValue("window/width", 800);
  // settings->setValue("window/height", 600);

    int x = settings.value("window/xpos").toInt();
    int y = settings.value("window/ypos").toInt();
    int width = settings.value("window/width").toInt();
    int height = settings.value("window/height").toInt();

    /* window size and position */
    this->setGeometry(x, y+24, width, height); /* window size and position */
    this->setWindowTitle(tr("ODA-IDE")); /* setup title */
    createStatusbar(20);

    QIcon *windowIcon = new QIcon("./img/icon.png");
    this->setWindowIcon(*windowIcon);



    this->console->setup();
#if DEBUG == 1
    this->console->appendDebuginfo("Debug mode started");
#endif

}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{

    delete this->tab;
    delete this->menuBar;
    delete this->console;
    delete this->statusBar();

    saveGeometry();
    saveSettings();

    delete this;
}

/**
 * @brief MainWindow::createLayout
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

    verticalSplitter = new QSplitter();
    verticalSplitter->setOrientation(Qt::Vertical);
    horizontalSplitter = new QSplitter(Qt::Horizontal);

    menuBar = new QMenuBar();
    toolBar = new QToolBar();

    menuBar = new QMenuBar(topFiller);
    toolBar = new QToolBar(topFiller);
   // editor = new Editor();
    //highlighter = new Highlighter(editor->document());
    console = new Console();
    //tab = new QTabWidget();

   //TODO: this is not working yet
    fileManager = new FileManager();
    horizontalSplitter->addWidget(fileManager);
    horizontalSplitter->addWidget(verticalSplitter);
    tab =  new Tab();
    verticalSplitter->addWidget(tab);
    verticalSplitter->addWidget(console);

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

    /* add the first tab with editor */
    this->addTab();

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

void MainWindow::createButtons()
{
    QIcon *newWindowIcon = new QIcon("./img/icons/new_window.png");
    QIcon *newTabIcon = new QIcon("./img/icons/new_tab.png");
    QIcon *newFileIcon = new QIcon("./img/icons/new_file.png");
    QIcon *saveIcon = new QIcon("./img/icons/save.png");
    QIcon *buildIcon = new QIcon("./img/icons/build.png");
    QIcon *runIcon = new QIcon("./img/icons/run.png");

    newWindowButton = new QPushButton(*newWindowIcon, tr(""));
    toolBar->addWidget(newWindowButton);
    connect(newWindowButton, SIGNAL(clicked(bool)), this, SLOT(newWindow()));

    newTabButton= new QPushButton(*newTabIcon, tr(""));
    toolBar->addWidget(newTabButton);
    connect(newTabButton, SIGNAL(clicked(bool)), this, SLOT(addTab()));

    newFileButton = new QPushButton(*newFileIcon, tr(""));
    toolBar->addWidget(newFileButton);
    connect(newFileButton, SIGNAL(clicked(bool)), this, SLOT(newFile()));

    saveButton = new QPushButton(*saveIcon, tr(""));
    toolBar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));


    compileButton = new QPushButton(*buildIcon, tr(""));
    toolBar->addWidget(compileButton);

    runButton = new QPushButton(*runIcon, tr(""));
    toolBar->addWidget(runButton);

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

void MainWindow::addTab()
{
    Editor *tabeditor = new Editor();
    Highlighter *tabhighlighter = new Highlighter(tabeditor->document());
    this->tab->addTab(tabeditor, tr("(new)"));
    tab->setCurrentIndex(tab->count() - 1);

#if DEBUG == 1
    cout << "tabsnum:" << tab->count()<<endl;
#endif
}

void MainWindow::saveGeometry()
{
    qDebug() << "savegeometry\n";
}

/**
 * @brief MainWindow::saveSettings
 */
void MainWindow::saveSettings()
{
    QSettings settings(QString("configs/config.ini"), QSettings::IniFormat);
    settings.setValue("window/xpos", this->x());
    settings.setValue("window/ypos", this->y());
    settings.setValue("window/width", this->width());
    settings.setValue("window/height", this->height());

    qDebug() << this->x();

}

/**
 * @brief MainWindow::loadSettings
 */
void MainWindow::loadSettings()
{

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

    newTabAct = new QAction(tr("New &Tab"), this);
    newTabAct->setShortcuts(QKeySequence::AddTab);
    newTabAct->setStatusTip(tr("Create new tab"));
    connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(addTab()));

    newFileAct = new QAction(tr("New F&ile"), this);
    newFileAct->setStatusTip(tr("Create new File"));
    connect(newFileAct, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openFileAct = new QAction(tr("&Open File"), this);
    openFileAct->setShortcut(QKeySequence::Open);
    openFileAct->setStatusTip(tr("Open existing File"));
    connect(openFileAct, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    saveFileAct = new QAction(tr("&Save"), this);
    saveFileAct->setShortcut(QKeySequence::Save);
    saveFileAct->setStatusTip(tr("Save a file"));
    connect(saveFileAct, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    saveFileAsAct = new QAction(tr("Save as"), this);
    saveFileAsAct->setShortcut(QKeySequence::SaveAs);
    saveFileAsAct->setStatusTip(tr("Save as file"));
    connect(saveFileAsAct, SIGNAL(triggered(bool)), this, SLOT(saveAsFile()));

    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Close);
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

    undoAct = new QAction(tr("Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered(bool)), tab, SLOT(undo()));

    redoAct = new QAction(tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered(bool)), tab, SLOT(redo()));

    copyAct = new QAction(tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    connect(copyAct, SIGNAL(triggered(bool)), tab, SLOT(copy()));

    cutAct = new QAction(tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    connect(cutAct, SIGNAL(triggered(bool)), tab, SLOT(cut()));

    pasteAct = new QAction(tr("Paste"), this);
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
 * @brief MainWindow::saveFile
 */
void MainWindow::saveFile()
{
    Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());
    QString filename = currentEditor->getOpenedFileName();
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

/**
 * @brief MainWindow::saveAsFile
 * creates a new file and saves the content of the editor
 */
void MainWindow::saveAsFile()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As File"), tr("All files(*)"));

    if(filename.isEmpty()) {
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
        QString info = ">> " + filename + " saved\n";
        console->appendPlainText(info);
        statusBar()->showMessage(currentEditor->getFileExtension());

        file->write(currentEditor->toPlainText().toStdString().c_str());
        file->flush();
        file->close();
        emit(currentEditor->filenameChanged(filename));

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
            currentEditor->setFileNameAndExtension(filename);

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
    newWindows = new MainWindow(this);
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
