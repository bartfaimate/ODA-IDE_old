#include "Headers/mainwindow.h"
#include <QApplication>
#include <QErrorMessage>

#define TEST 0
#if TEST == 1
#include <QtTest/QTest>
#include "src/test.cpp"
#endif

int main(int argc, char *argv[])
{
#if TEST != 1
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
#endif
#if TEST == 1

#endif
}
