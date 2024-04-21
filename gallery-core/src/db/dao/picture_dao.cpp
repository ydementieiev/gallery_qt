#include "db/dao/picture_dao.h"

#include "db/database_manager.h"
#include "picture.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

PictureDao::PictureDao(QSqlDatabase &database) : mDatabase(database)
{
}

void PictureDao::init() const
{
    if (!mDatabase.tables().contains("pictures"))
    {
        QSqlQuery query(mDatabase);
        query.exec(QString("CREATE TABLE pictures")
        + " (id INTEGER PRIMARY KEY AUTOINCREMENTS, "
        + "album_id INTEGER, "
        + "url TEXT)");
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO pictures (album_id, url) VALUES (:album_id, :url)");
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.fileUrl());
    query.exec();
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void PictureDao::removePicturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE album_id = :album_id");
    query.bindValue(":album_id", albumId);
    query.exec();
}

PictureDao::PictureVectorPtr PictureDao::picturesForAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = :album_id");
    query.bindValue(":album_id", albumId);
    query.exec();

    PictureVectorPtr list = std::make_unique<PictureVector>();
    while (query.next())
    {
        auto picture = std::make_unique<Picture>();
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileUrl(query.value("url").toString());

        list->push_back(std::move(picture));
    }
    return list;
}
