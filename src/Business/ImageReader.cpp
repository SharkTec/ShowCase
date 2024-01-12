#include "ImageReader.h"

#include <QDebug>
#include <QImage>

QImage ImageReader::readImage(const QString &filename) const
{
    QImage image;
    if(!image.load(filename)){
        qDebug() << QString("Could not load file: %1").arg(filename);
    }
    return image;
}

