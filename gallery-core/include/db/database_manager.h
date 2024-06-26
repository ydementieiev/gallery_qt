#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "db/dao/album_dao.h"
#include "db/dao/picture_dao.h"

#include <QString>

class QSqlDatabase;

const QString DATABASE_FILENAME = "galerry.db";

class DatabaseManager
{

public:
    static DatabaseManager &instance();
    ~DatabaseManager();

protected:
    DatabaseManager(const QString &path = DATABASE_FILENAME);
    DatabaseManager &operator=(const DatabaseManager &rhs);

private:
    QSqlDatabase *mDatabase;

public:
    const AlbumDao mAlbumDao;
    const PictureDao mPictureDao;
};

#endif // DATABASE_MANAGER_H
