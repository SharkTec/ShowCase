#include "ImageReader.h"
#include "Logger.h"

#include <QImage>

QImage ImageReader::readImage(const QString& filename) const
{
    QImage image;
    if(!image.load(filename))
    {
        Logger::getInstance()->logMessage("Could not load file.");
    }
    return image;
}
