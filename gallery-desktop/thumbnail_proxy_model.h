#ifndef THUMBNAIL_PROXY_MODEL_H
#define THUMBNAIL_PROXY_MODEL_H

#include <QIdentityProxyModel>
#include <QHash>
#include <QPixmap>
#include <QVariant>

class PictureModel;

class ThumbnailProxyModel : public QIdentityProxyModel
{
public:
    ThumbnailProxyModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const override;
    void setSourceModel(QAbstractItemModel *sourceModel) override;
    PictureModel *pictureModel() const;

private:
    void reloadThumbnails();
    void generateThumbnails(const QModelIndex &startIndex, int count);

private:
    QHash<QString, QPixmap *> mThumbnails;
};

#endif // THUMBNAIL_PROXY_MODEL_H
