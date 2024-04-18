#ifndef ALBUM_DAO_H
#define ALBUM_DAO_H

#include <QVector>

class QSqlDatabase;
class Album;

class AlbumDao
{
public:
    AlbumDao(QSqlDatabase &database);

    void init() const;

    void addAlbum(Album &album) const;
    void updateAlbum(const Album &album) const;
    void removeAlbum(int id) const;
    QVector<Album *> albums() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // ALBUM_DAO_H
