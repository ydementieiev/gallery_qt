#ifndef ALBUM_H
#define ALBUM_H

#include "gallery-core_global.h"

#include <QString>

class GALLERYCORE_EXPORT Album
{
public:
    explicit Album(const QString &name = QString());

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

private:
    int mId = -1;
    QString mName;
};

#endif // ALBUM_H
