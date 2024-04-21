#ifndef PICTURE_DAO_H
#define PICTURE_DAO_H

#include <memory>
#include <vector>

class QSqlDatabase;
class Picture;

class PictureDao
{
    using PictureVector = std::vector<std::unique_ptr<Picture>>;
    using PictureVectorPtr = std::unique_ptr<PictureVector>;

public:
    explicit PictureDao(QSqlDatabase &database);

    void init() const;

    void addPictureInAlbum(int albumId, Picture &picture) const;
    void removePicture(int id) const;
    void removePicturesForAlbum(int albumId) const;
    PictureVectorPtr picturesForAlbum(int albumId) const;

private:
    QSqlDatabase &mDatabase;
};

#endif // PICTURE_DAO_H
