#include "Headers/settings.h"
#include <QTabWidget>

Settings::Settings(QDialog *parent)
{
    this->setGeometry(40,40,400,600);
    this->setWindowTitle(tr("Settings"));
    createLayout();

  // this->setModality(Qt::WindowModality::WindowModal);
}

Settings::~Settings()
{
    delete this;
}

void Settings::createFontSettings()
{
    //TODO: finish this. maybe new class for fontsettings
}

void Settings::createBuildSettings()
{
    //TODO: finish this. maybe new class for buildsettings
}

void Settings::createLayout()
{
    QWidget *mainWidget = new QWidget;
    QWidget *widget = new QWidget;
    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->addTab(mainWidget, tr("Haho"));
    tabWidget->addTab(widget, tr("haha"));
}
