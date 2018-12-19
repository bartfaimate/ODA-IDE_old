#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileIconProvider>
#include <QDebug>


class FileManager : public QTreeView
{
    Q_OBJECT
public:
    explicit FileManager(QWidget *parent = nullptr);

signals:

public slots:
    void printPath(const QModelIndex &index);

private:
    QFileSystemModel *model;
};

#endif // FILEMANAGER_H
