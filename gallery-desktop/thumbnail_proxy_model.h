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
    ThumbnailProxyModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;
    void setSourceModel(QAbstractItemModel* sourceModel) override;
    PictureModel* pictureModel() const;

private:
    void generateThumbnails(const QModelIndex& startIndex, int count);
    void reloadThumbnails();

private:
    QHash<QString, QPixmap*> mThambnails;
};

#endif // THUMBNAIL_PROXY_MODEL_H
