#pragma once

#include <QObject>
#include <QPixmap>

class QString;
class QImage;


class ImageReader
{
    ImageReader() = default;
public:
    QImage readImage(const QString &filename) const;
};
