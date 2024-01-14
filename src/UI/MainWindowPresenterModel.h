#pragma once

#include <QObject>
#include <QImage>

/* this model class is currently not used because there is only the image data that needs to be stored
and this exact image data is already stored in the QGraphicsScene with the addPixmap method in MainWindow

So, for the sake of simplicity I just used a QPixmap member in MainWindow.

If there will be more data to be stored in the future (or the need to save/persist data) using this
presenter model would be the correct and maintainable way to go.

*/

class MainWindowPresenterModel : public QObject
{
public:
    explicit MainWindowPresenterModel(QObject* parent);

    ~MainWindowPresenterModel() = default;

    void setModelData(const QImage& image);
    QImage getModelData() const;

    QImage m_image;
};
