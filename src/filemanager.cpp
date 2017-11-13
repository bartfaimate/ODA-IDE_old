#include "Headers/filemanager.h"

FileManager::FileManager(QWidget *parent) : QWidget(parent)
{
    QFileSystemModel model;
    model.setRootPath("");

    QTreeView tree;
    tree.setModel(&model);


    // Demonstrating look and feel features
    tree.setAnimated(false);
    tree.setIndentation(20);
    tree.setSortingEnabled(true);

}
