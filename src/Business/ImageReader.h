#pragma once

class QString;
class QImage;

class ImageReader
{
public:

    ImageReader() = default;
    ~ImageReader() = default;

    QImage readImage(const QString& filename) const;
};
