#include "Headers/mainwindow.h"
#include <QApplication>
#include <QErrorMessage>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    QFile File("css/dark.qss");

    if (File.exists()) {
        try{
            File.open(QFile::ReadOnly);
            QString StyleSheet = QLatin1String(File.readAll());

            a.setStyleSheet(StyleSheet);
        }
        catch (...) {
            QErrorMessage *fileError = new QErrorMessage();
            fileError->showMessage("Stylesheet file not found");
        }
    }


    return a.exec();
}
