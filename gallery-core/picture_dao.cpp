#include "picture_dao.h"

#include "database_manager.h"
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

void PictureDao::removePicturesFromAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE album_id = :album_id");
    query.bindValue(":album_id", albumId);
    query.exec();
}

QVector<Picture*> PictureDao::picturesFromAlbum(int albumId) const
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = :album_id");
    query.bindValue(":album_id", albumId);
    query.exec();

    QVector<Picture*> list;
    while (query.next())
    {
        Picture* picture = new Picture();
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileUrl(query.value("url").toString());
        
        list.append(picture);
    }
    return list;
}


