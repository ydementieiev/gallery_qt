#include "thumbnail_proxy_model.h"

#include "models/picture_model.h"

const unsigned int THUMBNAUL_SIZE = 350;

ThumbnailProxyModel::ThumbnailProxyModel(QObject* parent)
    : QIdentityProxyModel(parent)
{
}

QVariant ThumbnailProxyModel::data(const QModelIndex& index, int role) const
{
    if(role != Qt::DecorationRole)
    {
        return QIdentityProxyModel::data(index, role);
    }

    QString filePath = sourceModel()->data(index, PictureModel::Roles::FilePathRole).toString();
    return *mThambnails[filePath];
}

void ThumbnailProxyModel::setSourceModel(QAbstractItemModel* sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    if(!sourceModel)
    {
        return;
    }

    connect(sourceModel, &QAbstractItemModel::modelReset, [this]{ reloadThumbnails(); });
    connect(sourceModel, &QAbstractItemModel::rowsInserted,
            [this](const QModelIndex& parent, int first, int last)
            {
                generateThumbnails(index(first, 0), last - first + 1);
            }
    );
}

PictureModel* ThumbnailProxyModel::pictureModel() const
{
    return static_cast<PictureModel*>(sourceModel());
}


void ThumbnailProxyModel::generateThumbnails(const QModelIndex& startIndex, int count)
{
    if(!startIndex.isValid())
    {
        return;
    }

    const QAbstractItemModel* model = startIndex.model();
    int lastIndex = startIndex.row() + count;
    for (int row = 0; row < lastIndex; ++row)
    {
        QString filePath = model->data(model->index(row,0), PictureModel::Roles::FilePathRole).toString();
        QPixmap pixmap(filePath);
        auto thumbnail = new QPixmap(pixmap.scaled(THUMBNAUL_SIZE, THUMBNAUL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        mThambnails.insert(filePath, thumbnail);
    }
}

void ThumbnailProxyModel::reloadThumbnails()
{
    qDeleteAll(mThambnails);
    mThambnails.clear();
    generateThumbnails(index(0,0), rowCount());
}
