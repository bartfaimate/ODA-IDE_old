#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileIconProvider>

class FileManager : public QWidget
{
    Q_OBJECT
public:
    explicit FileManager(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // FILEMANAGER_H
