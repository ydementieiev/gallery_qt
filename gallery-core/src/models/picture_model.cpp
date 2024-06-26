#include "models/picture_model.h"

#include "db/database_manager.h"
#include "models/album_model.h"

using namespace std;

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent)
    : QAbstractListModel(parent)
    , mDb(DatabaseManager::instance())
    , mAlbumId(-1)
    , mPictures(new vector<unique_ptr<Picture>>())
{
    connect(&albumModel, &AlbumModel::rowsRemoved,
            this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture& picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    unique_ptr<Picture> newPicture(new Picture(picture));
    mDb.mPictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures->push_back(std::move(newPicture));
    endInsertRows();

    return index(rows, 0);
}

int PictureModel::rowCount(const QModelIndex& /*parent*/) const
{
    return mPictures->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const Picture& picture = *mPictures->at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
        return picture.fileUrl().fileName();

    case Roles::UrlRole:
        return picture.fileUrl();

    case Roles::FilePathRole:
        return picture.fileUrl().toLocalFile();

    default:
        return QVariant();
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0
        || row >= rowCount()
        || count < 0
        || (row + count) > rowCount()) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while(countLeft--)
    {
        const Picture& picture = *mPictures->at(row + countLeft);
        mDb.mPictureDao.removePicture(picture.id());
    }
    mPictures->erase(mPictures->begin() + row,
                     mPictures->begin() + row + count);
    endRemoveRows();


    return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::FilePathRole] = "filepath";
    return roles;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum()
{
    mDb.mPictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId <= 0)
    {
        mPictures.reset(new vector<unique_ptr<Picture>>());
        return;
    }
    mPictures = mDb.mPictureDao.picturesForAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex& index) const
{
    if (index.row() < 0
        || index.row() >= rowCount()
        || !index.isValid()) {
        return false;
    }
    return true;
}
