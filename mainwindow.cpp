#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    window(new Ui::MainWindow)
{

    /* widget is mainwidget*/
    QWidget *mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    hBoxLayout = new QHBoxLayout(); /* horizontal layout */

    //ui->setupUi(this);
    menuBar = new QMenuBar(topFiller);
    toolBar = new QToolBar(topFiller);
    editor = new Editor();

    QVBoxLayout *layout = new QVBoxLayout(); /* vertical layout */
    layout->setMargin(5);
    layout->addWidget(menuBar);
    layout->addWidget(toolBar);
    layout->addLayout(hBoxLayout);

    mainWidget->setLayout(layout);

    hBoxLayout->addWidget(toolBar);
    hBoxLayout->addWidget(editor);

    this->setLayout(hBoxLayout);
    //this->show();

    createActions();
    createMenus();

    this->setGeometry(50, 50, 800, 600); /* window size and position */
    this->setWindowTitle(tr("ODA-IDE")); /* setup title */
    createStatusbar(20);

}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete window;
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
    //connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

    newFileAct = new QAction(tr("New F&ile"), this);
    newFileAct->setStatusTip(tr("Create new File"));
    //connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

    openFileAct = new QAction(tr("&Open File"), this);
    openFileAct->setStatusTip(tr("Open existing File"));
    //connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

    saveFileAct = new QAction(tr("&Save"), this);
    saveFileAct->setShortcut(QKeySequence::Save);
    saveFileAct->setStatusTip(tr("Save a file"));
    //connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

    saveFileAsAct = new QAction(tr("Save as"), this);
    saveFileAsAct->setShortcut(QKeySequence::SaveAs);
    saveFileAsAct->setStatusTip(tr("Save as file"));
    //connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

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
    undoAct = new QAction(tr("Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered(bool)), editor, SLOT(undo()));

    redoAct = new QAction(tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered(bool)), editor, SLOT(redo()));

    copyAct = new QAction(tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    connect(copyAct, SIGNAL(triggered(bool)), editor, SLOT(copy()));

    cutAct = new QAction(tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
    connect(cutAct, SIGNAL(triggered(bool)), editor, SLOT(cut()));

    pasteAct = new QAction(tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    connect(pasteAct, SIGNAL(triggered(bool)), editor, SLOT(paste()));
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
 * @brief MainWindow::newWindow
 * creates new window
 */
void MainWindow::newWindow()
{
    newWindows = new MainWindow(this);
    newWindows->show();
}
