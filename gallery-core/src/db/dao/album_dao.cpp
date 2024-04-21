#include "db/dao/album_dao.h"

#include "db/database_manager.h"
#include "album.h"

#include <QSqlDatabase>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>

AlbumDao::AlbumDao(QSqlDatabase &database) : mDatabase(database)
{
}

void AlbumDao::init() const
{
    if (!mDatabase.tables().contains("albums"))
    {
        QSqlQuery query(mDatabase);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENTS, name TEXT)");
    }
}

void AlbumDao::addAlbum(Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("INSERT INTO albums (name) VALUES (:name)");
    query.bindValue(":name", album.name());
    query.exec();

    album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlQuery query(mDatabase);
    query.prepare("UPDATE albums SET name = :name WHERE id = :id");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
}

void AlbumDao::removeAlbum(int id) const
{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM albums WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

AlbumDao::AlbumVectorPtr AlbumDao::albums() const
{
    QSqlQuery query("SELECT * FROM albums", mDatabase);
    query.exec();

    AlbumVectorPtr list = std::make_unique<AlbumVector>();

    while (query.next())
    {
        auto album = std::make_unique<Album>();
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());

        list->push_back(std::move(album));
    }

    return list;
}
