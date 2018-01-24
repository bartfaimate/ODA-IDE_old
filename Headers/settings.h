#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QWindow>
#include <QDialog>

class Settings: public QDialog
{
    Q_OBJECT

public:
    Settings(QDialog *parent = 0);
    ~Settings();

private:

public slots:

public:
    void createFontSettings();
    void createBuildSettings();
signals:
    void fontsizeChnaged(int);

};

#endif // SETTINGS_H
