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
    createMenus();
    createActions();
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
}

void MainWindow::createActions()
{
    newWindowAct = new QAction(tr("&New Window"), this);
    newWindowAct->setShortcuts(QKeySequence::New);
    newWindowAct->setStatusTip(tr("Create a new window"));
    //connect(newWindowAct, &QAction::triggered, this, &MainWindow::MainWindow());

}
