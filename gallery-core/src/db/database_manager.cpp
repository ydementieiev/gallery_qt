#include "db/database_manager.h"

#include <QSqlDatabase>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString &path)
    : mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
    , mAlbumDao(*mDatabase)
    , mPictureDao(*mDatabase)
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();

    mAlbumDao.init();
    mPictureDao.init();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}
