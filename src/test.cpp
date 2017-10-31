#define TEST 0

#if TEST == 1
#include <QTest>
#include <QObject>
#include <Headers/editor.h>


class TestEditor: public QObject
{

private slots:
    void test_getFileExtension();
    void data_getFileExtension();
};

void TestEditor::test_getFileExtension()
{
    Editor editor();
    QFETCH(QString, filename);
    QFETCH(QString, extension);

    QCOMPARE(editor.getFileExtension(filename), extension);

}

void TestEditor::data_getFileExtension()
{
    QTest::addColumn<QString>("filename");
    QTest::addColumn<QString>("extension");

     QTest::newRow("absolute path") << "/home/mate/Desktop/test.txt" << "txt";
     QTest::newRow("relative path") << "Desktop/test.txt" << "txt";
     QTest::newRow("file with point") << "hello.1.c" << "c";
     QTest::newRow("relative path with point") << "./Desktop/hello.1.c" << "c";
}

QTEST_MAIN(TestEditor)

//#include "../QtProjects/build-CodeEditor-Desktop_Qt_5_9_0_GCC_64bit-Debug/test.moc"
#endif
