#ifndef PICTURE_H
#define PICTURE_H

#include "gallery-core_global.h"

#include <QUrl>
#include <QString>

class GALLERYCORE_EXPORT Picture
{
public:
    Picture(const QString &filePath = QString());
    Picture(const QUrl &fileUrl);

    int id() const;
    void setID(int id);

    int albumId() const;
    void setAlbumId(int albumId);

    QUrl fileUrl() const;
    void setFileUrl(const QUrl &fileUrl);

private:
    int mId = -1;
    int mAlbumId = -1;
    QUrl mFileUrl;
};

#endif // PICTURE_H
