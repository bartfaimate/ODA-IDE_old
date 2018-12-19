#include "sqlhandler.h"
#include <QtDebug>
#include <QFile>
#include <QProcess>
#include <QSqlError>

SQLHandler::SQLHandler(QObject *parent) : QObject(parent)
{

}

SQLHandler::~SQLHandler()
{
    if(dataBase.isOpen()){
        dataBase.close();
    }

}

SQLHandler::SQLHandler(QString pathToDB)
{
    this->databasePath = pathToDB;
    this->ID = 0;

    QFile *dbFile = new QFile(pathToDB);

    /* if dbase doesn't exist creata a sqlite3 dbase */
    if(!dbFile->exists()) {
        qDebug() <<  pathToDB << "Database does not exist";
    }
    else {

        /* create the slqite3 database handler */
        dataBase = QSqlDatabase::addDatabase("QSQLITE");
        dataBase.setDatabaseName(databasePath);

        if (!dataBase.open()) {
            qDebug() << "Error: connection with database fail: " << pathToDB;
        }
        else {
            qDebug() << "Database: connection ok";
        }
    }
    delete dbFile;
}

QString SQLHandler::getDatabasePath() const
{
    return databasePath;
}

void SQLHandler::setDatabasePath(const QString &databasePath)
{
    this->databasePath = databasePath;
}

///**
// * @brief SQLHandler::addRecord
// * @param data is a structure to be saved
// * @return true if recorrd added succesfully
// */
//bool SQLHandler::addRecord(LanguageData* data)
//{
//    bool succes = false;
//    QSqlQuery *query = new QSqlQuery();
//    //long int id = this->ID;

////    query->prepare("INSERT INTO Pictures ( Name, imgscolor, imgframemonotimes, imgsize, frameindex, imgdreslevel) "
////                   "VALUES ( :picName, :imgColor, :imgFramemonotimes, :imgSize, :frameIndex, :dreslevel);");

////    query->bindValue(":picName", data.imgName);
////    query->bindValue(":imgColor", data.imgsColor);
////    query->bindValue(":imgFramemonotimes", data.imgframeMonotimes);
////    query->bindValue(":imgSize", data.imgSize);
////    query->bindValue(":frameIndex", data.imgFrameIndex);
////    query->bindValue(":dresLevel", data.imgDresLevel);
//    if(query->exec()) {
//        succes = true;
//        this->ID++;
//    }
//    else {
//        qDebug() << "addPictures error:  " << query->lastError().text();
//    }
//    return succes;
//}



bool SQLHandler::addRecord(ExtensionData* data)
{
    bool success = false;

    return success;
}

bool SQLHandler::addRecord(LanguageData* data)
{
    bool success = false;

    return success;
}

bool SQLHandler::createLanguageTable()
{

}

bool SQLHandler::createExtensuonTable()
{

}

bool SQLHandler::queryKeyWords()
{

}

bool SQLHandler::queryInlineComment()
{

}

///**
// * @brief SQLHandler::createTable
// * @return true if the table created successfully
// */
//bool SQLHandler::createTable()
//{
//    bool success = false;

//    QSqlQuery *query = new QSqlQuery();

//    query->prepare("CREATE TABLE Pictures (id integer primary key autoincrement, "
//                   "Name varchar(20), imgscolor integer, imgframemonotimes integer, imgsize integer,"
//                   "imgdreslevel integer, frameindex integer);");

//    if(query->exec()) {
//        success = true;
//    }
//    else {
//        qDebug() << "Couldn't create the table 'Pictures': one might already exist.";
//    }
//    return success;
//}
