#ifndef PICTURE_DAO_H
#define PICTURE_DAO_H

#include <QVector>

class QSqlDatabase;
class Picture;

class PictureDao
{
public:
    explicit PictureDao(QSqlDatabase &database);

    void init() const;

    void addPictureInAlbum(int albumId, Picture &picture) const;
    void removePicture(int id) const;
    void removePicturesFromAlbum(int albumId) const;
    QVector<Picture *> picturesFromAlbum(int albumId) const;

private:
    QSqlDatabase &mDatabase;
};

#endif // PICTURE_DAO_H
