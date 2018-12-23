#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileIconProvider>
#include <QDebug>
#include <QFileInfo>

class FileManager : public QTreeView
{
    Q_OBJECT
public:
    explicit FileManager(QWidget *parent = nullptr);

    ~FileManager();

    bool fileExist(QString path);

signals:
    void filePath(QString);

public slots:
    void pathEmitter(const QModelIndex & index);
    void printPath(const QModelIndex &index);

private:
    QFileSystemModel *model;
};

#endif // FILEMANAGER_H
