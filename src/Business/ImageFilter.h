
#pragma once

class QImage;

class ImageFilter
{
public:
    ImageFilter() = default;
    QImage filterImage(QImage& sourceImage) const;
};
