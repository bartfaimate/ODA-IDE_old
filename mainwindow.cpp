#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    window(new Ui::MainWindow)
{

    QWidget *widget = new QWidget;
    setCentralWidget(widget);
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

     hBoxLayout = new QHBoxLayout();

    //ui->setupUi(this);
    menuBar = new QMenuBar(topFiller);
    toolBar = new QToolBar(topFiller);
    editor = new Editor();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addLayout(hBoxLayout);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);



    hBoxLayout->addWidget(menuBar);
    hBoxLayout->addWidget(toolBar);
    hBoxLayout->addWidget(editor);


    this->setLayout(hBoxLayout);
    //this->show();

    createActions();
    createMenus();

}

MainWindow::~MainWindow()
{
    delete window;
}

void MainWindow::createMenus()
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

    editMenu = menuBar->addMenu(tr("&Edit"));


    compilerMenu = menuBar->addMenu(tr("Com&piler"));

    helpMenu = menuBar->addMenu(tr("&Help"));

}

/**
 * @brief MainWindow::createActions
 * This function creates menu elements and actions for them.
 */
void MainWindow::createActions()
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

void MainWindow::newWindow()
{
    newWindows = new MainWindow(this);
    newWindows->show();
}
