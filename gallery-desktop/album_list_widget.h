#ifndef ALBUM_LIST_WIDGET_H
#define ALBUM_LIST_WIDGET_H

#include <QWidget>
#include <QItemSelectionModel>

namespace Ui {
class AlbumListWidget;
}
class AlbumModel;

class AlbumListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumListWidget(QWidget *parent = nullptr);
    ~AlbumListWidget();

    void setModel(AlbumModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

private slots:
    void createAlbum();

private:
    Ui::AlbumListWidget *ui;
    AlbumModel* mAlbumModel;
};

#endif // ALBUM_LIST_WIDGET_H
