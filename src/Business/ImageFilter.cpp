#include "ImageFilter.h"

#include <QMatrix3x3>
#include <QImage>

QImage ImageFilter::filterImage(QImage& srcImage) const
{
    //initialize resulting image with params of the source image
    QImage edges(srcImage.width(), srcImage.height(), srcImage.format());

    //*Generic 3x3 Filter Kernel for edge detection
    QMatrix3x3 kernel;
    kernel(0, 0) = -1; kernel(0, 1) = -1; kernel(0, 2) = -1;
    kernel(1, 0) = -1; kernel(1, 1) = 8; kernel(1, 2) = -1;
    kernel(2, 0) = -1; kernel(2, 1) = -1; kernel(2, 2) = -1;

    //convert color image to a grayscale image
    for(int i = 1; i < srcImage.width() -1; ++i)
    {
        for(int j = 1; j < srcImage.height() -1; ++j)
        {
            const uint pixVal = static_cast<uint>(qGray(srcImage.pixel(i, j)));
            srcImage.setPixel(i, j, pixVal);
        }
    }

    //process convolution
    for(int i = 1; i < srcImage.width() -1; ++i)
    {
        for(int j = 1; j < srcImage.height() -1; ++j)
        {
            float convPixVal =
                    kernel(0, 0) * qGray(srcImage.pixel(i + 1, j + 1)) +
                    kernel(0, 1) * qGray(srcImage.pixel(i, j + 1)) +
                    kernel(0, 2) * qGray(srcImage.pixel(i - 1, j + 1)) +

                    kernel(1, 0) * qGray(srcImage.pixel(i + 1, j)) +
                    kernel(1, 1) * qGray(srcImage.pixel(i, j)) +
                    kernel(1, 2) * qGray(srcImage.pixel(i - 1, j)) +

                    kernel(2, 0) * qGray(srcImage.pixel(i + 1, j - 1)) +
                    kernel(2, 1) * qGray(srcImage.pixel(i, j - 1)) +
                    kernel(2, 2) * qGray(srcImage.pixel(i - 1, j - 1));

            const int pixVal = static_cast<int>(convPixVal);
            edges.setPixel(i,j, qRgb(pixVal, pixVal, pixVal));
        }
    }

    return edges;
}
