#ifndef ALBUM_DAO_H
#define ALBUM_DAO_H

#include <memory>
#include <vector>

class QSqlDatabase;
class Album;

class AlbumDao
{
    using AlbumVector = std::vector<std::unique_ptr<Album>>;
    using AlbumVectorPtr = std::unique_ptr<AlbumVector>;

public:
    explicit AlbumDao(QSqlDatabase &database);

    void init() const;

    void addAlbum(Album &album) const;
    void updateAlbum(const Album &album) const;
    void removeAlbum(int id) const;
    AlbumVectorPtr albums() const;

private:
    QSqlDatabase &mDatabase;
};

#endif // ALBUM_DAO_H
