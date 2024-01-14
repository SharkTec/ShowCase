#pragma once

#include "ImageReader.h"
#include "ImageFilter.h"

#include <memory>

class ImageUtilityProvider
{
public:
    ImageUtilityProvider() = default;

    ~ImageUtilityProvider() = default;

    QImage loadImage(const QString& imagePath);

    void filterImage(QImage& image);

    std::unique_ptr<ImageReader> m_imageReader;
    std::unique_ptr<ImageFilter> m_imageFilter;
};

