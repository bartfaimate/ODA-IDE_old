#ifndef SQLHANDLER_H
#define SQLHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

struct ExtensionData;
struct LanguageData;

class SQLHandler : public QObject
{
    Q_OBJECT
public:
    explicit SQLHandler(QObject *parent = nullptr);
    ~SQLHandler();

    SQLHandler(QString pathToDB);

    QString getDatabasePath() const;
    void setDatabasePath(const QString &databasePath);

signals:


private:
    QString databasePath;
    QSqlDatabase dataBase;
    int ID;
public slots:
    bool addRecord(ExtensionData* data);
    bool addRecord(LanguageData* data);
    bool createLanguageTable();
    bool createExtensuonTable();
    bool queryKeyWords();
    bool queryInlineComment();
};

struct LanguageData{
public:
    QString name;
    QString inlineComment;
    QString multilineComment;
    QString stringFormat;
    QString functionFormat;
    QString keyWords;
};

struct ExtensionData{
public:
    int languageID;
    QString extension;
};

#endif // SQLHANDLER_H
