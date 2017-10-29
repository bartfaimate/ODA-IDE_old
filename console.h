#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QWidget>

class Console : public QWidget
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // CONSOLE_H