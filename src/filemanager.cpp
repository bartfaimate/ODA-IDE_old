#include "Headers/filemanager.h"
#include <iostream>

FileManager::FileManager(QWidget *parent) : QTreeView (parent)
{
    model = new QFileSystemModel();
    this->setModel(model);
    model->setRootPath(QDir::currentPath());

//    QTreeView *tree = new QTreeView();
//    tree->setModel(model);


    // Demonstrating look and feel features
    this->setAnimated(false);
    this->setIndentation(20);
    this->setSortingEnabled(true);

    this->hideColumn(1);
    this->hideColumn(2);
    this->hideColumn(3);

    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(printPath(QModelIndex)));

}

void FileManager::printPath(const QModelIndex &index)
{
    qDebug() << model->filePath(index) << "\n";

}
